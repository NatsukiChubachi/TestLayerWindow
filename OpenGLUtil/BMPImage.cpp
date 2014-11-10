
#include <fstream>
#include <windows.h>
#include "BMPImage.h"

using namespace std;

/*! �R���X�g���N�^
*/
CBMPImage::CBMPImage()
{
	this->m_iColorKey[0] = 0;
	this->m_iColorKey[1] = 0;
	this->m_iColorKey[2] = 0;
}

/*! �f�X�g���N�^
*/
CBMPImage::~CBMPImage()
{
}

/* BMP�C���[�W�ǂݍ���
*/
bool CBMPImage::ReadBMP(const char *filename)
{
    FILE *fp;

    BITMAPINFOHEADER bitmapInfoHeader;
    BITMAPFILEHEADER header;
    GLubyte temp = 0;

    //�@�t�@�C�����J��
    if ( (fp = fopen(filename, "rb")) == NULL )
    {
        cout << "Error : �w�肳�ꂽ�t�@�C�����J���܂���\n";
        cout << "File Name : " << filename << endl;
        return false;
    }

    //�@�w�b�_�[���̓ǂݎ��
    fread(&header, sizeof(BITMAPFILEHEADER), 1, fp);

    //�@�t�@�C���`�F�b�N
    if ( header.bfType != 0x4d42 )
    {
        cout << "Error : Bitmap�t�@�C���ł͂���܂���\n";
        fclose(fp);
        return false;
    }

    //�@�w�b�_�[���̓ǂݎ��
    fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    //�@���ƍ������擾
    width = bitmapInfoHeader.biWidth;
    height = bitmapInfoHeader.biHeight;

    if ( bitmapInfoHeader.biSizeImage == 0 )
    {
        bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 3;
    }

    fseek(fp, header.bfOffBits, SEEK_SET);

    //�@�f�[�^�T�C�Y�����肵�C���������m��
    imageSize = bitmapInfoHeader.biSizeImage;
    imageData = new GLubyte [imageSize];

    //�@�G���[�`�F�b�N
    if ( !imageData )
    {
        cout << "Error : ���������m�ۂł��܂���ł���\n";
        delete [] imageData;
        fclose(fp);
        return false;
    }

    //�@�s�N�Z���f�[�^�̓ǂݍ���
    fread(imageData, 1, bitmapInfoHeader.biSizeImage, fp);

    //�@BGR�@���@RGB�ɕϊ�
    for ( int i=0; i<(int)imageSize; i+=3 )
    {
        temp = imageData[i+0];
        imageData[i+0] = imageData[i+2];
        imageData[i+2] = temp;
    }

	// �e�N�X�`���o�^�Ɏg�p����C���[�W�f�[�^���쐬����
	// RGBA��4byte���擾����
	image2Size = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 4;
	image2Data = new GLubyte [image2Size];

	// �J���[�L�[���Q�Ƃ��ē���F�̏ꍇ�̓��ŐF�𔲂�
    for ( int i=0, index=0; i<(int)imageSize; i+=3, index++ )
    {
		image2Data[index*4+0] = imageData[i+0];
		image2Data[index*4+1] = imageData[i+1];
		image2Data[index*4+2] = imageData[i+2];
		image2Data[index*4+3] = 255;

		// ����F�̏ꍇ
		if(image2Data[index*4+0] == this->m_iColorKey[0]
			&& image2Data[index*4+1] == this->m_iColorKey[1]
			&& image2Data[index*4+2] == this->m_iColorKey[2]
			)
		{
			image2Data[index*4+3] = 0;
		}
	}

    //�@�t�@�C�������
    fclose(fp);

    return true;
}

/*! �e�N�X�`���ǂݍ���
*/
GLuint CBMPImage::load(const char *filename)
{
    if ( !ReadBMP(filename) )
	{
        return 0;
	}

	// �e�N�X�`���̍쐬
    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);

	// �e�N�X�`���ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// �e�N�X�`���ɃC���[�W�f�[�^��o�^����
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2Data);

	// �m�ۂ��Ă����C���[�W�f�[�^�̉��
    if ( imageData )
    {
        delete[] imageData;
        imageData = NULL;

		delete[] image2Data;
		image2Data = NULL;
    }

	// �o�^�����e�N�X�`��ID��Ԃ�
    return ID;
}

/*! �J���[�L�[�i�����F�j�ݒ�
*/
void CBMPImage::setColorKey(int iR, int iG, int iB)
{
	this->m_iColorKey[0] = iR;
	this->m_iColorKey[1] = iG;
	this->m_iColorKey[2] = iB;
}
