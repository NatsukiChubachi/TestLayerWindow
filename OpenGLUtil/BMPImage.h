//
//　include
//
#pragma once 

#include <iostream>
#include <GL/gl.h>
using namespace std;


/////////////////////////////////////////////////////////////////////////
//　　BMPImage class
/////////////////////////////////////////////////////////////////////////
class CBMPImage
{
private:
    GLuint imageSize;						// 元イメージのサイズ
    GLubyte *imageData;						// 元イメージデータ
	
    GLuint image2Size;						// テクスチャ登録のイメージサイズ
	GLubyte  *image2Data;					// テクスチャ登録のイメージサイズ

    GLenum format;							// イメージフォーマット
    GLuint internalFormat;					// イメージフォーマット
    GLuint width;							// イメージサイズWidth	
    GLuint height;							// イメージサイズHeight
    GLuint bpp;								// ビット数

    GLuint ID;								// テクスチャID

private:
    bool ReadBMP(const char *filename);		// BMPイメージの読み込み

public:
	CBMPImage();							// コンストラクタ
	~CBMPImage();							// デストラクタ
    
	GLuint load(const char *filename);		// テクスチャ読み込み
	void setColorKey(int iR, int iG, int iB);	// カラーキー（透明色）設定

private:
	int m_iColorKey[3];						// カラーキー

};