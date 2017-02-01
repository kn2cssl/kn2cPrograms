#-------------------------------------------------
#
# Project created by QtCreator 2012-01-29T16:05:56
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kn2cssl
TEMPLATE = app
#CONFIG   += qt warn_on incremental link_prl
#MAKEFILE_GENERATOR = UNIX
#TARGET_PLATFORM  = unix
#QMAKE_INCREMENTAL_STYLE = sublib
QMAKE_CXXFLAGS += -std=c++11

#CONFIG += debug
#CONFIG   += release
#DEFINES += QT_NO_DEBUG_OUTPUT

#QMAKE_CXXFLAGS += --coverage
#QMAKE_LFLAGS += --coverage

#QMAKE_CFLAGS    -= -O2 -O1
#QMAKE_CXXFLAGS  -= -O2 -O1
##QMAKE_CFLAGS  += -O3 -m64
##QMAKE_LFLAGS  += -O3 -m64
#QMAKE_CFLAGS  += -O3
#QMAKE_LFLAGS  += -O3
#QMAKE_CXXFLAGS += -O3

#QMAKE_CXXFLAGS += -O3
#QMAKE_CXXFLAGS += -m64
#QMAKE_CXXFLAGS += -pipe
#QMAKE_CXXFLAGS += -mmmx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mpclmul # -mavx -mavx2 -maes -mfsgsbase -mrdrnd
#QMAKE_CXXFLAGS += -mfpmath=sse
#QMAKE_CXXFLAGS += -fargument-noalias-global
#QMAKE_CXXFLAGS += -fomit-frame-pointer
##QMAKE_CXXFLAGS += -fwhole-program #fail!
#QMAKE_CXXFLAGS += -march=native
#QMAKE_CXXFLAGS += -mtune=native

#load(qt_config)

DESTDIR = ../bin
OBJECTS_DIR = ../tmp/.obj
MOC_DIR = ../tmp/.moc
RCC_DIR = ../tmp/.rcc
UI_DIR = ../tmp/.ui

unix:  LIBS += -lprotobuf -L/usr/local/lib -ligraph -L/usr/include/ -lCGAL -lgmp -lmpfr

#win32
#{
#    QMAKE_CXXFLAGS += -U__STRICT_ANSI__
#    LIBS += -L$$PWD/../ -lprotobuf
#    INCLUDEPATH += $$PWD/../
#    DEPENDPATH += $$PWD/../


#    INCLUDEPATH += C:/boost_1_55_0/
#    INCLUDEPATH += C:/boost_1_55_0/boost/
##   INCLUDEPATH += C:/protobuf-2.5.0/src/
#    INCLUDEPATH += C:/protobuf-2.4.1/src/

#    LIBS += -LC:/boost_1_55_0/lib
##   LIBS += -lboost_serialization-mgw46-mt-d-1_55
##   LIBS += -lboost_filesystem-mgw46-mt-d-1_55
##   LIBS += -lboost_system-mgw46-mt-d-1_55
#}

INCLUDEPATH += ssl
INCLUDEPATH += ssl/sslvision
INCLUDEPATH += ssl/sslvision/messages
INCLUDEPATH += ssl/sslrefbox
INCLUDEPATH += etc
INCLUDEPATH += ui
INCLUDEPATH += util
INCLUDEPATH += qextserialport
INCLUDEPATH += geom
INCLUDEPATH += output
INCLUDEPATH += grSim
INCLUDEPATH += ai

SOURCES +=	main.cpp \
    ssl/sslreceiver.cpp \
    ssl/sslrefbox.cpp \
    ssl/sslvision.cpp \
    ui/mainwindow.cpp \
    ui/renderarea.cpp \
    util/fpscounter.cpp \
    ai/soccer.cpp \
    ssl/worldmodel.cpp \
    output/wpacket.cpp \
    output/transmitter.cpp \
    output/grsim.cpp \
    output/grpacket.cpp \
    ssl/sslrefbox/game_state.cpp \
    ssl/mobileobject.cpp \
    ssl/ball.cpp \
    ssl/robot.cpp \
    output/controller.cpp \
    ai/ai.cpp \
    geom/angle_deg.cpp \
    geom/circle_2d.cpp \
    geom/composite_region_2d.cpp \
    geom/convex_hull.cpp \
    geom/delaunay_triangulation.cpp \
    geom/line_2d.cpp \
    geom/matrix_2d.cpp \
    geom/polygon_2d.cpp \
    geom/ray_2d.cpp \
    geom/rect_2d.cpp \
    geom/sector_2d.cpp \
    geom/segment_2d.cpp \
    geom/triangle_2d.cpp \
    geom/vector_2d.cpp \
    ai/agent.cpp \
    ai/navigation.cpp \
    ai/play.cpp \
    ai/tactic.cpp \
    ai/play/playtest.cpp \
    ai/tactic/tactictest.cpp \
    ai/mapsearchnode.cpp \
    ai/tactic/tacticgoalie.cpp \
    ai/tactic/tacticdefender.cpp \
    ai/tactic/tacticstop.cpp \
    ai/tactic/tactichalt.cpp \
    ai/tactic/tacticattacker.cpp \
    ai/knowledge.cpp \
    ai/tactic/tacticballtracker.cpp \
    ai/tactic/tacticcircle.cpp \
    ai/play/playstop.cpp \
    ai/play/playhalt.cpp \
    ai/play/playfreekickopp.cpp \
    ai/play/playfreekickour.cpp \
    ai/play/playgameon.cpp \
    ai/play/playkickoffopp.cpp \
    ai/play/playkickoffour.cpp \
    ai/play/playpenaltyopp.cpp \
    ai/play/playpenaltyour.cpp \
    ai/tactic/tactictestkickprecision.cpp \
    ai/tactic/tactictestfriction.cpp \
    ssl/sslrefboxnew.cpp \
    geom2/shape2d.cpp \
    ai/tactic/tacticblocker.cpp \
    ai/play/playtest2.cpp \
    ai/tactic/tacticfixedpos.cpp \
    ai/tactic/tactictechnical.cpp \
    ai/tactic/tacticpenaltykicker.cpp \
    ai/tactic/tactictest2.cpp \
    ai/tactic/tacticpreparing.cpp \
    ai/play/playpreparing.cpp \
    ai/mwbm.cpp \
    ai/man2man.cpp \
    geom/voronoi_diagram.cpp \
    ai/positioning.cpp \
    ai/play/playcontrol.cpp \
    ai/tactic/tacticcontrol.cpp \
    ai/play/freeKicks/freekick_base.cpp \
    ai/play/freeKicks/freekick1.cpp \
    ai/play/freeKicks/freekick2.cpp \
    ai/play/freeKicks/freekick3.cpp \
    ai/play/freeKicks/freekick4.cpp \
    ai/play/freeKicks/freekick5.cpp \
    ai/play/freeKicks/freekick6.cpp \
    ai/play/freeKicks/freekick7.cpp \
    ai/play/freeKicks/freekick8.cpp \
    ai/play/freeKicks/freekickdirect.cpp \
    ai/play/freeKicks/freekick9.cpp \
    ai/play/freeKicks/freekick10.cpp \
    ai/play/freeKicks/freekick11.cpp \
    ai/play/freeKicks/freekicktest1.cpp\
    ai/play/freeKicks/freekick47.cpp \
    etc/constants.cpp \
    ssl/sslvision_single.cpp \
    ssl/sslvision_double.cpp \
    ai/skill.cpp \
    ai/skill/skillkick.cpp \
    ai/skill/skilltest.cpp \
    ai/learning/hillclimbing.cpp \
    ai/learning/kick_learning.cpp \
    ai/learning/policy.cpp \
    ai/tactic/tactickicklearning.cpp \
    ai/play/playlearning.cpp \
    logplayer/logplayer.cpp \
    logplayer/vision_logplayer.cpp \
    logplayer/referee_logplayer.cpp \
    logplayer/ai_logplayer.cpp \
    proto/Ball_message.pb.cc \
    proto/grSim_Commands.pb.cc \
    proto/grSim_Packet.pb.cc \
    proto/grSim_Replacement.pb.cc \
    proto/log.pb.cc \
    proto/messages_robocup_ssl_detection.pb.cc \
    proto/messages_robocup_ssl_geometry.pb.cc \
    proto/messages_robocup_ssl_geometry_legacy.pb.cc \
    proto/messages_robocup_ssl_refbox_log.pb.cc \
    proto/messages_robocup_ssl_wrapper.pb.cc \
    proto/messages_robocup_ssl_wrapper_legacy.pb.cc \
    proto/position_message.pb.cc \
    proto/referee.pb.cc \
    proto/RobotCommand_message.pb.cc \
    proto/Robot_message.pb.cc \
    proto/ssl_log.pb.cc \
    proto/vision_log.pb.cc \
    proto/ref_log.pb.cc \
    ai/skill/skillpassreceive.cpp \
    ai/skill/skillonetouch.cpp \
    ai/tactic/tacticformation.cpp \
    ai/play/playformations.cpp \
<<<<<<< HEAD
    ai/tactic/tacticteststandingforwardenemy.cpp \
    ai/play/playhw2_1.cpp \
    ai/play/mantomandefense.cpp \
    ai/tactic/taticgoliealihejazi.cpp \
    ai/skill/shootball.cpp \
    ai/play/playstop_hejazi.cpp \
    ai/play/freeKicks/freekicktest2.cpp
=======
>>>>>>> 4bde963eede2897a0748e0221474ee6c1450efde

HEADERS  += \
    etc/settings.h \
    etc/constants.h \
    etc/base.h \
    ssl/worldmodel.h \
    ssl/sslreceiver.h \
    ssl/sslrefbox.h \
    ssl/sslrefbox/ref_protocol.h \
    ssl/sslrefbox/game_state.h \
    ssl/sslrefbox/commands.h \
    ssl/sslvision.h \
    ui/mainwindow.h \
    ui/renderarea.h \
    util/util.h \
    util/fpscounter.h \
    output/wpacket.h \
    output/transmitter.h \
    output/grsim.h \
    output/outputbuffer.h \
    output/grpacket.h \
    ssl/mobileobject.h \
    ssl/ball.h \
    ssl/robot.h \
    output/controller.h \
    ssl/position.h \
    ai/ai.h \
    ai/robotcommand.h \
    geom/angle_deg.h \
    geom/circle_2d.h \
    geom/composite_region_2d.h \
    geom/convex_hull.h \
    geom/delaunay_triangulation.h \
    geom/line_2d.h \
    geom/matrix_2d.h \
    geom/polygon_2d.h \
    geom/ray_2d.h \
    geom/rect_2d.h \
    geom/region_2d.h \
    geom/sector_2d.h \
    geom/segment_2d.h \
    geom/size_2d.h \
    geom/triangle_2d.h \
    geom/triangulation.h \
    geom/vector_2d.h \
    geom/geom.h \
    ai/soccer.h \
    ai/agent.h \
    ai/navigation.h \
    output/controller_struct.h \
    ai/play.h \
    ai/tactic.h \
    ai/play/playtest.h \
    ai/tactic/tactictest.h \
    3rdparty/stlastar.h \
    3rdparty/fsa.h \
    ai/mapsearchnode.h \
    ai/tactic/tacticgoalie.h \
    ai/tactic/tacticdefender.h \
    ai/tactic/tacticstop.h \
    ai/tactic/tactichalt.h \
    ai/tactic/tacticattacker.h \
    ai/knowledge.h \
    ai/tactic/tacticballtracker.h \
    ai/tactic/tacticcircle.h \
    ai/tactics.h \
    ai/play/playstop.h \
    ai/play/playhalt.h \
    ai/play/playfreekickopp.h \
    ai/play/playfreekickour.h \
    ai/play/playgameon.h \
    ai/play/playkickoffopp.h \
    ai/play/playkickoffour.h \
    ai/play/playpenaltyopp.h \
    ai/play/playpenaltyour.h \
    ai/tactic/tactictestkickprecision.h \
    ai/tactic/tactictestfriction.h \
    ssl/sslrefboxnew.h \
    geom2/shape2d.h \
    ai/tactic/tacticblocker.h \
    ai/play/playtest2.h \
    ai/tactic/tacticfixedpos.h \
    ai/tactic/tactictechnical.h \
    ai/tactic/tacticpenaltykicker.h \
    ai/tactic/tactictest2.h \
    ai/tactic/tacticpreparing.h \
    ai/play/playpreparing.h \
    ai/mwbm.h \
    ai/man2man.h \
    geom/voronoi_diagram.h \
    ai/positioning.h \
    ai/play/playcontrol.h \
    ai/tactic/tacticcontrol.h \
    ai/play/freeKicks/freekick_base.h \
    ai/play/freeKicks/freekick1.h \
    ai/play/freeKicks/freeKicks.h \
    ai/play/freeKicks/freekick2.h \
    ai/play/freeKicks/freekick3.h \
    ai/play/freeKicks/freekick4.h \
    ai/play/freeKicks/freekick5.h \
    ai/play/freeKicks/freekick6.h \
    ai/play/freeKicks/freekick7.h \
    ai/play/freeKicks/freekick8.h \
    ai/play/freeKicks/freekickdirect.h \
    ai/play/freeKicks/freekick9.h \
    ai/play/freeKicks/freekick10.h \
    ai/play/freeKicks/freekick11.h \
    ai/play/freeKicks/freekicktest1.h\
    ai/play/freeKicks/freekick47.h \
    ssl/sslvision_single.h \
    ssl/sslvision_double.h \
    ai/skill.h \
    ai/skill/skillkick.h \
    ai/Skills.h \
    ai/skill/skilltest.h \
    ai/learning/hillclimbing.h \
    ai/learning/kick_learning.h \
    ai/learning/policy.h \
    ai/tactic/tactickicklearning.h \
    ai/play/playlearning.h \
    logplayer/logplayer.h \
    logplayer/vision_logplayer.h \
    logplayer/referee_logplayer.h \
    logplayer/ai_logplayer.h \
    proto/Ball_message.pb.h \
    proto/grSim_Commands.pb.h \
    proto/grSim_Packet.pb.h \
    proto/grSim_Replacement.pb.h \
    proto/log.pb.h \
    proto/messages_robocup_ssl_detection.pb.h \
    proto/messages_robocup_ssl_geometry.pb.h \
    proto/messages_robocup_ssl_geometry_legacy.pb.h \
    proto/messages_robocup_ssl_refbox_log.pb.h \
    proto/messages_robocup_ssl_wrapper.pb.h \
    proto/messages_robocup_ssl_wrapper_legacy.pb.h \
    proto/position_message.pb.h \
    proto/referee.pb.h \
    proto/RobotCommand_message.pb.h \
    proto/Robot_message.pb.h \
    proto/ssl_log.pb.h \
    proto/vision_log.pb.h \
    proto/ref_log.pb.h \
    ai/skill/skillpassreceive.h \
    ai/skill/skillonetouch.h \
    ai/tactic/tacticformation.h \
    ai/play/playformations.h \
<<<<<<< HEAD
    ai/tactic/tacticteststandingforwardenemy.h \
    ai/play/playhw2_1.h \
    ai/play/mantomandefense.h \
    ai/tactic/taticgoliealihejazi.h \
    ai/skill/shootball.h \
    ai/play/playstop_hejazi.h \
    ai/play/freeKicks/freekicktest2.h
=======
>>>>>>> 4bde963eede2897a0748e0221474ee6c1450efde

FORMS    +=	ui/mainwindow.ui

OTHER_FILES += \
    ../config/settings.ini \
    ../config/vars.ini

RESOURCES += \
    resources.qrc

