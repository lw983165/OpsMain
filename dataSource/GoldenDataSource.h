#pragma once

#include "IDataSource.h"
#include "Canvas.hpp"
#include "goldenapi.h"
#include "BatchValueChangeEvent.h"

#include <QMap>
#include <QSettings>
#include <QMutex>

enum SubType { S_Snapshot, S_Tag, S_History };
enum {POINT = 0, SCAN, CALC};

typedef std::tuple<GOLDEN_POINT*,  GOLDEN_SCAN_POINT*,  GOLDEN_CALC_POINT*> BIG_POINT;

class GoldenDataSource : public IDataSource
{
    static GoldenDataSource* instance;
public:
    GoldenDataSource(Canvas* canvas);

    static GoldenDataSource* getInstance();

    ///
    virtual int init(const char* config) override;
    virtual int start() override;
    virtual int stop() override;

    ///
    int on_tags_changed(golden_int32 count, const golden_int32 *ids, golden_int32 what);
    int on_data_changed(golden_int32 count,
                      const golden_int32 *ids,
                      const golden_int32 *datetimes,
                      const golden_int16 *ms,
                      const golden_float64 *values,
                      const golden_int64 *states,
                      const golden_int16 *qualities,
                      const golden_error *errors);

    int subscribe(golden_int32 count, const golden_int32 *ids, int type);
    int cancel_subscribe(int type);

    GOLDEN_POINT* getPointById(golden_int32 id);
    int addPointsFromServer(const golden_int32* ids, int count);
    int removePointsLocal(golden_int32* ids, int count);
    void update(BIG_POINT point);
    void releasePoint(golden_int32 id);

private:
    /// according to the SDK manual, callback handler must own special socket which not allowed using for other purpose
    golden_int32 apiHandle;
    golden_int32 cbTagsHandle;
    golden_int32 cbSnapHandle;
    gob_tags_change_event_ex tagsCallback;
    gos_snaps_event_ex snapsCallback;
    goh_data_playback_ex hisCallback;

    QSettings* conf;
    Canvas* canvas;

    QMap<golden_int32, BIG_POINT> points;
    QMutex mutex4points;

};

