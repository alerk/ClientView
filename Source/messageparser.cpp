#include "messageparser.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

typedef enum parsing_state_t
{
    IDLE = 0,
    FLAG_F1,
    FLAG_F2,
    FLAG_AA,
    FLAG_55,
    MSG_TYPE,//00: FireAlarm; 01: IntruderAlarm; 02: FireVideo
    MSG_VALUE,
    SOURCE_ID,
    COLS,
    ROWS,
    DEPTH,
    IDX,
    TOTAL,
    SIZE,
    DATA
}parsing_state;

static parsing_state current_state = IDLE;

MessageParser::MessageParser()
{

}

MessageParser::~MessageParser()
{

}

void MessageParser::parseMessage(unsigned int size, unsigned char *buffer, unsigned char &output_type, unsigned char &output_value, QImage &output)
{
    int i=0;
    unsigned char src_id;
    unsigned char cols;
    unsigned char rows;
    unsigned char depth;
    unsigned char idx;
    unsigned char total;
    unsigned int img_size;

    unsigned char* img_buffer;

    unsigned char data;

    for (i=0;i<size;i++)
    {
        data = buffer[i];
        switch (current_state)
        {
        case IDLE:
            if(data==0xFF)
            {
                current_state = FLAG_F1;
            }

            break;
        case FLAG_F1:
            if(data==0xFF)
            {
                current_state = FLAG_F2;
            }
            break;
        case FLAG_F2:
            if(data==0xAA)
            {
                current_state = FLAG_AA;
            }
            break;
        case FLAG_AA:
            if(data==0x55)
            {
                current_state = FLAG_55;
            }
            break;
        case FLAG_55:
        {
            current_state = MSG_TYPE;
            output_type = data;
        }
            break;
        case MSG_TYPE:
            if(output_type!=0x02)
            {
                current_state = IDLE;
                output_value = data;
                //emit something here
            }
            else
            {
                current_state = SOURCE_ID;
                src_id = data;
                output_value = data;
            }
            break;
        case SOURCE_ID:
        {
            cols = data;
            current_state = COLS;
        }
            break;
        case COLS:
        {
            rows = data;
            current_state = ROWS;
        }
            break;
        case ROWS:
        {
            depth = data;
            current_state = DEPTH;
        }
            break;
        case DEPTH:
        {
            idx = data;
            current_state = IDX;
        }
            break;
        case IDX:
        {
            total = data;
            current_state = TOTAL;
        }
            break;
        case TOTAL:
        {
            img_size = (unsigned int)(*(buffer+i));
            i+=3;
            current_state = SIZE;
        }
            break;
        case SIZE:
        {
            img_buffer = (buffer+i);
            current_state = DATA;
        }
            break;
        case DATA:
        {
            cv::Mat opencv_img(rows,cols,CV_8UC3,img_buffer);
            //            cv::Mat opencv_img(rows,cols,CV_8UC3);
            //            memcpy(opencv_img.data(), img_buffer, rows*cols*depth);
            cv::Mat temp; // make the same cv::Mat
            cv::cvtColor(opencv_img, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
            output = QImage((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
            output.bits();
        }
            break;
        default:
            break;
        }
    }
}

