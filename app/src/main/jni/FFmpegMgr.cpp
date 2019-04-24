//
// Created by jiaqi on 4/22/2019.
//


#include "FFmpegMgr.h"
#include "macro.h"
#include <cstring>
#include <pthread.h>

extern "C" {
#include <libavformat/avformat.h>
}

void *task_prepare(void *args) {
    FFmpegMgr *ffmpeg = static_cast<FFmpegMgr *>(args);
    ffmpeg->_prepare();
    return nullptr;
}

FFmpegMgr::FFmpegMgr(JavaCallHelper *callHelper, const char *dataSource) {
    this->dataSource = new char[strlen(dataSource) + 1];
    strcpy(this->dataSource, dataSource);
    this->callHelper = callHelper;
}

FFmpegMgr::~FFmpegMgr() {
    DELETE(dataSource);
    DELETE(callHelper);
}

void FFmpegMgr::prepare() {
    pthread_create(&tid, nullptr, task_prepare, this);
}

void FFmpegMgr::_prepare() {

//    avformat_network_init();

    // 1.打开媒体地址（本地 or 网络）
    formatContext = nullptr;
    int ret = avformat_open_input(&formatContext, dataSource, 0, 0);
    // 非0表示失败
    if (ret) {
        callHelper->onError(THREAD_CHILD, FFMPEG_CAN_NOT_OPEN_URL);
        char *msg = av_err2str(ret);
        LOGE("FFMPEG_CAN_NOT_OPEN_URL::::::");
        LOGE("%s", msg);
        return;
    }

    // 2.查找媒体中的音视频流
    ret = avformat_find_stream_info(formatContext, nullptr);
    // 小于0表示失败
    if (ret < 0) {
        callHelper->onError(THREAD_CHILD, FFMPEG_CAN_NOT_FIND_STREAMS);
        LOGE("FFMPEG_CAN_NOT_FIND_STREAMS");
        return;
    }

    for (int i = 0; i < formatContext->nb_streams; ++i) {
        AVStream *avStream = formatContext->streams[i];
        AVCodecParameters *codecpar = avStream->codecpar;

        AVCodec *decoder = avcodec_find_decoder(codecpar->codec_id);
        if (decoder == nullptr) {
            callHelper->onError(THREAD_CHILD, FFMPEG_FIND_DECODER_FAIL);
            LOGE("FFMPEG_FIND_DECODER_FAIL");
            return;
        }

        AVCodecContext *avCodecContext = avcodec_alloc_context3(decoder);
        if (avCodecContext == nullptr) {
            callHelper->onError(THREAD_CHILD, FFMPEG_ALLOC_CODEC_CONTEXT_FAIL);
            LOGE("FFMPEG_ALLOC_CODEC_CONTEXT_FAIL");
            return;
        }

        ret = avcodec_parameters_to_context(avCodecContext, codecpar);
        if (ret < 0) {
            callHelper->onError(THREAD_CHILD, FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            LOGE("FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL");
            return;
        }

        ret = avcodec_open2(avCodecContext, decoder, nullptr);
        if (ret != 0) {
            callHelper->onError(THREAD_CHILD, FFMPEG_OPEN_DECODER_FAIL);
            LOGE("FFMPEG_OPEN_DECODER_FAIL");
            return;
        }

        if (codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audioChannel = new AudioChannel;
        } else if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoChannel = new VideoChannel;
        }
    }

    if (!audioChannel && !videoChannel) {
        callHelper->onError(THREAD_CHILD, FFMPEG_NOMEDIA);
        LOGE("FFMPEG_NOMEDIA");
        return;
    }

    callHelper->onPrepare(THREAD_CHILD);
}

