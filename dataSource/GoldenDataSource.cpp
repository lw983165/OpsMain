#include "GoldenDataSource.h"

#include <QDebug>
#include <QDateTime>
#include <QApplication>

golden_error on_tags_change (golden_int32 count, const golden_int32 *ids, golden_int32 what)
{
    return  GoldenDataSource::getInstance()->on_tags_changed(count, ids, what);
}

golden_error on_data_change (golden_int32 count,
                              const golden_int32 *ids,
                              const golden_int32 *datetimes,
                              const golden_int16 *ms,
                              const golden_float64 *values,
                              const golden_int64 *states,
                              const golden_int16 *qualities,
                              const golden_error *errors)
{
    return GoldenDataSource::getInstance()->on_data_changed(count, ids, datetimes, ms, values, states, qualities, errors);
}

GoldenDataSource* GoldenDataSource::instance = nullptr;

GoldenDataSource::GoldenDataSource(Canvas* canvas)
{
    apiHandle = 0;
    cbTagsHandle = 0;
    cbSnapHandle = 0;
    tagsCallback = nullptr;
    snapsCallback = nullptr;
    conf = nullptr;

    this->canvas = canvas;

    instance = this;
}

GoldenDataSource *GoldenDataSource::getInstance()
{
    return instance;
}

int GoldenDataSource::init(const char *config)
{
    if (conf) {
        qDebug() << "already inited!" ;
        return 0;
    }
    conf = new QSettings(config, QSettings::IniFormat);
    if (!conf->contains("/golden/server")) {
        qDebug() << "file: " << config << " not contains[/golden/server]";
        return -1;
    }
    if (!conf->contains("/golden/port")) {
        qDebug() << "file: " << config << " not contains[/golden/port]";
        return -1;
    }
    return 0;
}

int GoldenDataSource::start()
{
    if (!conf) {
        qDebug() << "not inited!" ;
        return -1;
    }
    QString host = conf->value("/golden/server").toString();
    int port = conf->value("/golden/port").toInt();
    golden_error ret = go_connect(host.toStdString().c_str(), port, &apiHandle);
    if (ret != GoE_OK) {
        qDebug() << "connect to host[" << host << "], port[" << port << "] failed! error_code[" << ret << "]";
        return ret;
    }

    ///
    ret = go_connect(host.toStdString().c_str(), port, &cbTagsHandle);
    if (ret != GoE_OK) {
        qDebug() << "connect to host[" << host << "], port[" << port << "] failed! error_code[" << ret << "]";
        return ret;
    }

    ret = go_connect(host.toStdString().c_str(), port, &cbSnapHandle);
    if (ret != GoE_OK) {
        qDebug() << "connect to host[" << host << "], port[" << port << "] failed! error_code[" << ret << "]";
        return ret;
    }

    return 0;
}

int GoldenDataSource::stop()
{
    if (cbTagsHandle) {
        gob_cancel_subscribe_tags (cbTagsHandle);
        go_disconnect(cbTagsHandle);
        cbTagsHandle = 0;
    }
    if (cbSnapHandle) {
        gos_cancel_subscribe_snapshots (cbSnapHandle);
        go_disconnect(cbSnapHandle);
        cbSnapHandle = 0;
    }
    if (apiHandle) {
        go_disconnect(apiHandle);
        apiHandle = 0;
    }
    return 0;
}

int GoldenDataSource::on_tags_changed(golden_int32 count, const golden_int32 *ids, golden_int32 what)
{
    switch (what) {
    case GOLDEN_TAG_CHANGE_REASON::GOLDEN_TAG_CREATED:
    case GOLDEN_TAG_CHANGE_REASON::GOLDEN_TAG_UPDATED:
    case GOLDEN_TAG_CHANGE_REASON::GOLDEN_TAG_RECOVERD:
        qDebug() << "reload points from server";
        addPointsFromServer(ids, count);
        break;
    case GOLDEN_TAG_CHANGE_REASON::GOLDEN_TAG_REMOVED:
    case GOLDEN_TAG_CHANGE_REASON::GOLDEN_TAG_PURGED:
        qDebug() << "remove local points";
        removePointsLocal(const_cast<golden_int32 *>(ids), count);
        break;
    case GOLDEN_TAG_CHANGE_REASON::GOLDEN_TAB_UPDATED:
    case GOLDEN_TAG_CHANGE_REASON::GOLDEN_TAB_REMOVED:
        qDebug() << "tab event, not sure what should i do";
        break;
    default:
        break;
    }
    return 0;
}

int GoldenDataSource::on_data_changed(golden_int32 count,
                                      const golden_int32 *ids,
                                      const golden_int32 *datetimes,
                                      const golden_int16 *ms,
                                      const golden_float64 *values,
                                      const golden_int64 *states,
                                      const golden_int16 *qualities,
                                      const golden_error *errors)
{
    BIG_POINT point;

    ///
    BatchValueChangeEvent* event = new BatchValueChangeEvent();
    for (int i = 0; i < count; i++, ids++, datetimes++, ms++,  values++, states++, qualities++, errors++) {
        if (*errors != GoE_OK) continue;
        if (!points.contains(*ids)) addPointsFromServer(ids, 1);
        if (!points.contains(*ids)) continue;
        point = points[*ids];
        if (*qualities != GOLDEN_QUALITY::GOLDEN_Q_GOOD) continue;
        /// format time
        QDateTime time = QDateTime::fromTime_t(*datetimes);
        QString strTime = time.toString("yyyy-MM-ddThh:mm:ss");
        if (std::get<0>(point)->millisecond) strTime.append(":").append(*ms);
        /// format value
        QString strVal;
        switch (std::get<0>(point)->type) {
        case GOLDEN_REAL16:
        case GOLDEN_REAL32:
        case GOLDEN_REAL64:
            strVal = QString::number(*values, 'f', 5);
            break;
        case GOLDEN_BOOL:
        case GOLDEN_UINT8:
        case GOLDEN_INT8:
        case GOLDEN_CHAR:
        case GOLDEN_UINT16:
        case GOLDEN_INT16:
        case GOLDEN_UINT32:
        case GOLDEN_INT32:
        case GOLDEN_INT64:
            strVal = QString::number(*states);
        default:
            return -1;
        }
        UiValue* val = new UiValue();
        val->data_id = *ids;
        val->ui_id = "";
        val->time = strTime;
        val->value_type = std::get<0>(point)->type;
        val->value = strVal;
        event->add(val);
    }

    ///
    QApplication::sendEvent(canvas, event);
    return 0;
}


int GoldenDataSource::subscribe(golden_int32 count, const golden_int32 *ids, int type)
{
    golden_error *errors = new golden_error[count];
    if (type == S_Snapshot) gos_subscribe_snapshots(cbSnapHandle,  &count, ids, on_data_change, errors);
    else if (type == S_Tag) gob_subscribe_tags(cbTagsHandle, on_tags_change);
    delete[] errors;
    return 0;
}

int GoldenDataSource::cancel_subscribe(int type)
{
    if (type == S_Snapshot) gos_cancel_subscribe_snapshots (cbSnapHandle);
    else if (type == S_Tag) gob_cancel_subscribe_tags (cbTagsHandle);
    return 0;
}

GOLDEN_POINT *GoldenDataSource::getPointById(golden_int32 id)
{
    if (!points.contains(id))
        addPointsFromServer(&id, 1);
    return std::get<0>(points[id]);
}

int GoldenDataSource::addPointsFromServer(const golden_int32 *ids, int count)
{
    ///
    GOLDEN_POINT *point = new GOLDEN_POINT[count];
    GOLDEN_POINT *p = point;
    golden_int32 *pIds = const_cast<golden_int32 *>(ids);
    for(int i = 0; i < count; i++, p++, pIds++) p->id = *pIds;

    GOLDEN_SCAN_POINT* scan = new GOLDEN_SCAN_POINT[count];
    GOLDEN_CALC_POINT* calc = new GOLDEN_CALC_POINT[count];
    golden_error* err = new golden_error[count];
    golden_error ret = gob_get_points_property(apiHandle, count, point, scan, calc, err);
    if (ret == GoE_OK) {
        GOLDEN_POINT* p = point;
        GOLDEN_SCAN_POINT* pScan = scan;
        GOLDEN_CALC_POINT* pCalc = calc;
        golden_int32 *pIds = const_cast<golden_int32 *>(ids);;
        golden_error* pErr = err;
        mutex4points.lock();
        for(int i = 0; i < count; i++, p++, pScan++, pCalc++, pIds++, pErr++) {
            if (*pErr == GoE_OK)
                update(std::make_tuple(p, pScan, pCalc));
        }
        mutex4points.unlock();

        return 0;
    } else {
        return ret;
    }
}

int GoldenDataSource::removePointsLocal(golden_int32 *ids, int count)
{
    mutex4points.lock();
    for (int i = 0; i < count; i++, ids++) releasePoint(*ids);
    mutex4points.unlock();
    return 0;
}

void GoldenDataSource::update(BIG_POINT point)
{
    golden_int32 id = std::get<0>(points[id])->id;
    releasePoint(id);
    points[id] = point;
}

void GoldenDataSource::releasePoint(golden_int32 id)
{
    if (points.contains(id)) {
        BIG_POINT old = points[id];
        delete std::get<0>(old);
        delete std::get<1>(old);
        delete std::get<2>(old);
        points.remove(id);
    }
}
