#include "messageparser.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define IMG_BUFFER_SIZE 928332

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

static parsing_state next_state = IDLE;
static unsigned char img_buffer[IMG_BUFFER_SIZE];
static unsigned long img_idx=0;

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

    unsigned char data;

    for (i=0;i<size;i++)
    {
        data = buffer[i];
        switch (next_state)
        {
        case IDLE:
            if(data==0xFF)
            {
                next_state = FLAG_F1;
            }

            break;
        case FLAG_F1:
            if(data==0xFF)
            {
                next_state = FLAG_F2;
            }
            break;
        case FLAG_F2:
            if(data==0xAA)
            {
                next_state = FLAG_AA;
            }
            break;
        case FLAG_AA:
            if(data==0x55)
            {
                next_state = FLAG_55;
            }
            break;
        case FLAG_55:
        {
            next_state = MSG_TYPE;
            output_type = data;
        }
            break;
        case MSG_TYPE:
            if(output_type!=0x02)
            {
                next_state = IDLE;
                output_value = data;
                //emit something here
            }
            else
            {
                next_state = SOURCE_ID;
                src_id = data;
                output_value = data;
            }
            break;
        case SOURCE_ID:
        {
            cols = data;
            next_state = COLS;
        }
            break;
        case COLS:
        {
            rows = data;
            next_state = ROWS;
        }
            break;
        case ROWS:
        {
            depth = data;
            next_state = DEPTH;
        }
            break;
        case DEPTH:
        {
            idx = data;
            next_state = IDX;
        }
            break;
        case IDX:
        {
            total = data;
            next_state = SIZE;
        }
            break;
//        case TOTAL:
//        {
//            img_size = (unsigned int)(*(buffer+i));
//            i+=3;
//            next_state = SIZE;
//        }
//            break;
        case SIZE:
        {
            img_buffer[img_idx++] = data;
            //memcpy(img_buffer,(buffer+i),IMG_BUFFER_SIZE);
            next_state = DATA;
        }
            break;
        case DATA:
        {
            img_buffer[img_idx++] = data;
            if(img_idx == IMG_BUFFER_SIZE)
            {
                cv::Mat opencv_img(cv::Size(24*20+2,32*20+2),CV_8UC3,img_buffer);
                //            cv::Mat opencv_img(rows,cols,CV_8UC3);
                //            memcpy(opencv_img.data(), img_buffer, rows*cols*depth);
                //cv::imshow("Recv img", opencv_img);
                cv::Mat temp; // make the same cv::Mat
                cv::cvtColor(opencv_img, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
                output = QImage((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                output.bits();
                output_type = 2;
                output_value = 6;
                next_state = IDLE;
                img_idx = 0;
            }
        }
            break;
        default:
            break;
        }
    }
}

