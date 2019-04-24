//
// Created by jiaqi on 4/22/2019.
//

#ifndef AEOPLAYER_AEOFFMPEG_H
#define AEOPLAYER_AEOFFMPEG_H

#include <string>
#include "JavaCallHelper.h"
#include "AudioChannel.h"
#include "VideoChannel.h"

extern "C" {
#include <libavformat/avformat.h>
}

class FFmpegMgr {
public:
    FFmpegMgr(JavaCallHelper *callHelper, const char *dataSource);

    ~FFmpegMgr();

    void prepare();

    void _prepare();

private:
    char *dataSource;
    pthread_t tid;
    AVFormatContext *formatContext;
    JavaCallHelper *callHelper;
    AudioChannel *audioChannel;
    VideoChannel *videoChannel;
};


#endif //AEOPLAYER_AEOFFMPEG_H
