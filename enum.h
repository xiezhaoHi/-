#ifndef ENUM_H
#define ENUM_H
#include<QString>
//����һЩ��������
typedef struct{
    int flag; //��ʶ������ʲô
    QString strData;//�����������
}struct_data;

//������ݱ�ʶ
enum enum_detection
{
    detection_dy, //��ѹ
     detection_dl, //����
     detection_aqcd,//��ȫ����
     detection_hxdlwz,//�������λ��
     detection_slyxsd, //ʸ�������ٶ�
    detection_pcjd,//ƽ�㾫�ȣ��������ڼ�����������
    detection_jgyl,//��Ҫ������λ�ṹӦ��
                        //��˿��ʹ��״̬
    detection_gssnwbds, //��˿�����ⲿ��˿

                    //����/���ᾲ̬ˮƽ�ȼ�⹦�ܣ�
    detection_spd,//����/����ˮƽ��

                    //����/�������мӡ����ٶȼ�⹦��
    detection_jjsd,//����/��������мӼ��ٶ�
    detection_zdjl,//�ƶ�������Զ���⹦�� �ƶ�����
};

#endif // ENUM_H
