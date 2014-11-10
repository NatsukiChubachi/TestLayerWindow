//
//�@include
//
#pragma once 

#include <iostream>
#include <GL/gl.h>
using namespace std;


/////////////////////////////////////////////////////////////////////////
//�@�@BMPImage class
/////////////////////////////////////////////////////////////////////////
class CBMPImage
{
private:
    GLuint imageSize;						// ���C���[�W�̃T�C�Y
    GLubyte *imageData;						// ���C���[�W�f�[�^
	
    GLuint image2Size;						// �e�N�X�`���o�^�̃C���[�W�T�C�Y
	GLubyte  *image2Data;					// �e�N�X�`���o�^�̃C���[�W�T�C�Y

    GLenum format;							// �C���[�W�t�H�[�}�b�g
    GLuint internalFormat;					// �C���[�W�t�H�[�}�b�g
    GLuint width;							// �C���[�W�T�C�YWidth	
    GLuint height;							// �C���[�W�T�C�YHeight
    GLuint bpp;								// �r�b�g��

    GLuint ID;								// �e�N�X�`��ID

private:
    bool ReadBMP(const char *filename);		// BMP�C���[�W�̓ǂݍ���

public:
	CBMPImage();							// �R���X�g���N�^
	~CBMPImage();							// �f�X�g���N�^
    
	GLuint load(const char *filename);		// �e�N�X�`���ǂݍ���
	void setColorKey(int iR, int iG, int iB);	// �J���[�L�[�i�����F�j�ݒ�

private:
	int m_iColorKey[3];						// �J���[�L�[

};