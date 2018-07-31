#-------------------------------------------------
#
# Project created by QtCreator 2018-07-09T14:57:39
#
#-------------------------------------------------

QT       += core gui widgets svg network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MACSui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    commands/BringForwardCommand.cpp \
    commands/BringToFrontCommand.cpp \
    commands/BulkOrderCommand.cpp \
    commands/ChangeOrderCommand.cpp \
    commands/DeleteSelectedCommand.cpp \
    commands/DrawCommand.cpp \
    commands/MoveSelectionCommand.cpp \
    commands/SendBackwardCommand.cpp \
    commands/SendToBackCommand.cpp \
    events/ValueChangeEvent.cpp \
    fileio/FileReaderFactory.cpp \
    fileio/FileWriterFactory.cpp \
    fileio/HtJsonFileReader.cpp \
    fileio/JsonFileReader.cpp \
    fileio/JsonFileWriter.cpp \
    fileio/KyJsonFileReader.cpp \
    fileio/KyJsonFileReaderV2.cpp \
    shapes/Circle.cpp \
    shapes/Line.cpp \
    shapes/Rectangle.cpp \
    shapes/svg.cpp \
    shapes/Text.cpp \
    tools/DrawCircleTool.cpp \
    tools/DrawLineTool.cpp \
    tools/DrawRectangleTool.cpp \
    tools/SelectionTool.cpp \
    tools/ValueChangeTool.cpp \
    AbstractGroup.cpp \
    ActiveSelection.cpp \
    Canvas.cpp \
    Command.cpp \
    CommandStack.cpp \
    GlobalDrawProperties.cpp \
    Group.cpp \
    MainCommandStack.cpp \
    PropertyColorButton.cpp \
    PropertySpinBox.cpp \
    Selection.cpp \
    Shape.cpp \
    Tool.cpp \
    VisualEntity.cpp \
    commands/BringForwardCommand.cpp \
    commands/BringToFrontCommand.cpp \
    commands/BulkOrderCommand.cpp \
    commands/ChangeOrderCommand.cpp \
    commands/DeleteSelectedCommand.cpp \
    commands/DrawCommand.cpp \
    commands/MoveSelectionCommand.cpp \
    commands/SendBackwardCommand.cpp \
    commands/SendToBackCommand.cpp \
    common/PropertySupport.cpp \
    dataSource/GoldenDataSource.cpp \
    events/BatchValueChangeEvent.cpp \
    events/ValueChangeEvent.cpp \
    fileio/FileReaderFactory.cpp \
    fileio/FileWriterFactory.cpp \
    fileio/HtJsonFileReader.cpp \
    fileio/JsonFileReader.cpp \
    fileio/JsonFileWriter.cpp \
    fileio/KyJsonFileReader.cpp \
    fileio/KyJsonFileReaderV2.cpp \
    shapes/Circle.cpp \
    shapes/Line.cpp \
    shapes/Rectangle.cpp \
    shapes/svg.cpp \
    shapes/Text.cpp \
    tools/DrawCircleTool.cpp \
    tools/DrawLineTool.cpp \
    tools/DrawRectangleTool.cpp \
    tools/SelectionTool.cpp \
    tools/ValueChangeTool.cpp \
    AbstractGroup.cpp \
    ActiveSelection.cpp \
    Canvas.cpp \
    Command.cpp \
    CommandStack.cpp \
    GlobalDrawProperties.cpp \
    Group.cpp \
    main.cpp \
    MainCommandStack.cpp \
    mainwindow.cpp \
    PropertyColorButton.cpp \
    PropertySpinBox.cpp \
    Selection.cpp \
    Shape.cpp \
    Tool.cpp \
    VisualEntity.cpp \
    commands/BringForwardCommand.cpp \
    commands/BringToFrontCommand.cpp \
    commands/BulkOrderCommand.cpp \
    commands/ChangeOrderCommand.cpp \
    commands/DeleteSelectedCommand.cpp \
    commands/DrawCommand.cpp \
    commands/MoveSelectionCommand.cpp \
    commands/SendBackwardCommand.cpp \
    commands/SendToBackCommand.cpp \
    common/PropertySupport.cpp \
    dataSource/GoldenDataSource.cpp \
    events/BatchValueChangeEvent.cpp \
    events/ValueChangeEvent.cpp \
    fileio/FileReaderFactory.cpp \
    fileio/FileWriterFactory.cpp \
    fileio/HtJsonFileReader.cpp \
    fileio/JsonFileReader.cpp \
    fileio/JsonFileWriter.cpp \
    fileio/KyJsonFileReader.cpp \
    fileio/KyJsonFileReaderV2.cpp \
    shapes/Circle.cpp \
    shapes/Line.cpp \
    shapes/Rectangle.cpp \
    shapes/svg.cpp \
    shapes/Text.cpp \
    tools/DrawCircleTool.cpp \
    tools/DrawLineTool.cpp \
    tools/DrawRectangleTool.cpp \
    tools/SelectionTool.cpp \
    tools/ValueChangeTool.cpp \
    AbstractGroup.cpp \
    ActiveSelection.cpp \
    Canvas.cpp \
    Command.cpp \
    CommandStack.cpp \
    GlobalDrawProperties.cpp \
    Group.cpp \
    main.cpp \
    MainCommandStack.cpp \
    mainwindow.cpp \
    PropertyColorButton.cpp \
    PropertySpinBox.cpp \
    Selection.cpp \
    Shape.cpp \
    Tool.cpp \
    VisualEntity.cpp

HEADERS  += \
    commands/BringForwardCommand.hpp \
    commands/BringToFrontCommand.hpp \
    commands/BulkOrderCommand.hpp \
    commands/ChangeOrderCommand.hpp \
    commands/ChangePropertyCommand.hpp \
    commands/ChangePropertyCommandList.hpp \
    commands/DeleteSelectedCommand.hpp \
    commands/DrawCommand.hpp \
    commands/MoveSelectionCommand.hpp \
    commands/SendBackwardCommand.hpp \
    commands/SendToBackCommand.hpp \
    events/eventdef.h \
    events/ValueChangeEvent.h \
    fileio/FileReaderFactory.hpp \
    fileio/FileWriterFactory.hpp \
    fileio/HtJsonFileReader.h \
    fileio/JsonFileReader.hpp \
    fileio/JsonFileWriter.hpp \
    fileio/KyJsonFileReader.h \
    fileio/KyJsonFileReaderV2.h \
    interfaces/IDrawable.hpp \
    interfaces/IFileReader.hpp \
    interfaces/IFileWriter.hpp \
    interfaces/IFillable.hpp \
    interfaces/IImage.h \
    interfaces/ilabel.h \
    interfaces/ILine.hpp \
    interfaces/ISelectable.hpp \
    interfaces/ITransformable.hpp \
    shapes/Circle.hpp \
    shapes/jsondef.h \
    shapes/Line.hpp \
    shapes/Rectangle.hpp \
    shapes/svg.h \
    shapes/Text.h \
    tools/DrawCircleTool.hpp \
    tools/DrawLineTool.hpp \
    tools/DrawRectangleTool.hpp \
    tools/SelectionTool.hpp \
    tools/ValueChangeTool.h \
    Command.hpp \
    AbstractGroup.hpp \
    ActiveSelection.hpp \
    CommandStack.hpp \
    Selection.hpp \
    Signal.hpp \
    VisualEntity.hpp \
    Group.hpp \
    Shape.hpp \
    GlobalDrawProperties.hpp \
    Tool.hpp \
    Canvas.hpp \
    MainCommandStack.hpp \
    MainWindow.hpp \
    PropertyColorButton.hpp \
    PropertySpinBox.hpp \
    commands/BringForwardCommand.hpp \
    commands/BringToFrontCommand.hpp \
    commands/BulkOrderCommand.hpp \
    commands/ChangeOrderCommand.hpp \
    commands/ChangePropertyCommand.hpp \
    commands/ChangePropertyCommandList.hpp \
    commands/DeleteSelectedCommand.hpp \
    commands/DrawCommand.hpp \
    commands/MoveSelectionCommand.hpp \
    commands/SendBackwardCommand.hpp \
    commands/SendToBackCommand.hpp \
    common/PropertySupport.h \
    dataSource/GoldenDataSource.h \
    events/BatchValueChangeEvent.h \
    events/eventdef.h \
    events/ValueChangeEvent.h \
    fileio/FileReaderFactory.hpp \
    fileio/FileWriterFactory.hpp \
    fileio/HtJsonFileReader.h \
    fileio/JsonFileReader.hpp \
    fileio/JsonFileWriter.hpp \
    fileio/KyJsonFileReader.h \
    fileio/KyJsonFileReaderV2.h \
    interfaces/IDrawable.hpp \
    interfaces/IFileReader.hpp \
    interfaces/IFileWriter.hpp \
    interfaces/IFillable.hpp \
    interfaces/IImage.h \
    interfaces/ilabel.h \
    interfaces/ILine.hpp \
    interfaces/ISelectable.hpp \
    interfaces/ITransformable.hpp \
    shapes/Circle.hpp \
    shapes/jsondef.h \
    shapes/Line.hpp \
    shapes/Rectangle.hpp \
    shapes/svg.h \
    shapes/Text.h \
    tools/DrawCircleTool.hpp \
    tools/DrawLineTool.hpp \
    tools/DrawRectangleTool.hpp \
    tools/SelectionTool.hpp \
    tools/ValueChangeTool.h \
    AbstractGroup.hpp \
    ActiveSelection.hpp \
    Canvas.hpp \
    Command.hpp \
    CommandStack.hpp \
    DrawDialog.hpp \
    GlobalDrawProperties.hpp \
    Group.hpp \
    MainCommandStack.hpp \
    mainwindow.h \
    MainWindow.hpp \
    PropertyColorButton.hpp \
    PropertySpinBox.hpp \
    Selection.hpp \
    Shape.hpp \
    Signal.hpp \
    Tool.hpp \
    VisualEntity.hpp \
    commands/BringForwardCommand.hpp \
    commands/BringToFrontCommand.hpp \
    commands/BulkOrderCommand.hpp \
    commands/ChangeOrderCommand.hpp \
    commands/ChangePropertyCommand.hpp \
    commands/ChangePropertyCommandList.hpp \
    commands/DeleteSelectedCommand.hpp \
    commands/DrawCommand.hpp \
    commands/MoveSelectionCommand.hpp \
    commands/SendBackwardCommand.hpp \
    commands/SendToBackCommand.hpp \
    common/PropertySupport.h \
    dataSource/GoldenDataSource.h \
    events/BatchValueChangeEvent.h \
    events/eventdef.h \
    events/ValueChangeEvent.h \
    fileio/FileReaderFactory.hpp \
    fileio/FileWriterFactory.hpp \
    fileio/HtJsonFileReader.h \
    fileio/JsonFileReader.hpp \
    fileio/JsonFileWriter.hpp \
    fileio/KyJsonFileReader.h \
    fileio/KyJsonFileReaderV2.h \
    interfaces/IDataSource.h \
    interfaces/IDrawable.hpp \
    interfaces/IFileReader.hpp \
    interfaces/IFileWriter.hpp \
    interfaces/IFillable.hpp \
    interfaces/IImage.h \
    interfaces/ilabel.h \
    interfaces/ILine.hpp \
    interfaces/ipropertysupport.h \
    interfaces/ISelectable.hpp \
    interfaces/ITransformable.hpp \
    shapes/Circle.hpp \
    shapes/jsondef.h \
    shapes/Line.hpp \
    shapes/Rectangle.hpp \
    shapes/svg.h \
    shapes/Text.h \
    tools/DrawCircleTool.hpp \
    tools/DrawLineTool.hpp \
    tools/DrawRectangleTool.hpp \
    tools/SelectionTool.hpp \
    tools/ValueChangeTool.h \
    AbstractGroup.hpp \
    ActiveSelection.hpp \
    Canvas.hpp \
    Command.hpp \
    CommandStack.hpp \
    DrawDialog.hpp \
    GlobalDrawProperties.hpp \
    Group.hpp \
    MainCommandStack.hpp \
    mainwindow.h \
    MainWindow.hpp \
    PropertyColorButton.hpp \
    PropertySpinBox.hpp \
    Selection.hpp \
    Shape.hpp \
    Signal.hpp \
    Tool.hpp \
    VisualEntity.hpp

FORMS    += mainwindow.ui
DESTDIR = $$PWD/../build

INCLUDEPATH += \
    $$PWD \
    interfaces \
    commands \
    tools \
    shapes \
    events \
    fileio
DISTFILES += \
    icon.rc

RESOURCES += \
    icons.qrc
RC_FILE=icon.rc

win32:CONFIG(release, debug|release): LIBS += -L$$(GOLDEN_DIR)/ -lgoldenapi64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$(GOLDEN_DIR)/ -lgoldenapi64

INCLUDEPATH += $$(GOLDEN_DIR)/
DEPENDPATH += $$(GOLDEN_DIR)/
