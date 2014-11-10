
#include <fstream>
#include <windows.h>
#include "BMPImage.h"

using namespace std;

/*! コンストラクタ
*/
CBMPImage::CBMPImage()
{
	this->m_iColorKey[0] = 0;
	this->m_iColorKey[1] = 0;
	this->m_iColorKey[2] = 0;
}

/*! デストラクタ
*/
CBMPImage::~CBMPImage()
{
}

/* BMPイメージ読み込み
*/
bool CBMPImage::ReadBMP(const char *filename)
{
    FILE *fp;

    BITMAPINFOHEADER bitmapInfoHeader;
    BITMAPFILEHEADER header;
    GLubyte temp = 0;

    //　ファイルを開く
    if ( (fp = fopen(filename, "rb")) == NULL )
    {
        cout << "Error : 指定されたファイルが開けません\n";
        cout << "File Name : " << filename << endl;
        return false;
    }

    //　ヘッダー情報の読み取り
    fread(&header, sizeof(BITMAPFILEHEADER), 1, fp);

    //　ファイルチェック
    if ( header.bfType != 0x4d42 )
    {
        cout << "Error : Bitmapファイルではありません\n";
        fclose(fp);
        return false;
    }

    //　ヘッダー情報の読み取り
    fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    //　幅と高さを取得
    width = bitmapInfoHeader.biWidth;
    height = bitmapInfoHeader.biHeight;

    if ( bitmapInfoHeader.biSizeImage == 0 )
    {
        bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 3;
    }

    fseek(fp, header.bfOffBits, SEEK_SET);

    //　データサイズを決定し，メモリを確保
    imageSize = bitmapInfoHeader.biSizeImage;
    imageData = new GLubyte [imageSize];

    //　エラーチェック
    if ( !imageData )
    {
        cout << "Error : メモリが確保できませんでした\n";
        delete [] imageData;
        fclose(fp);
        return false;
    }

    //　ピクセルデータの読み込み
    fread(imageData, 1, bitmapInfoHeader.biSizeImage, fp);

    //　BGR　→　RGBに変換
    for ( int i=0; i<(int)imageSize; i+=3 )
    {
        temp = imageData[i+0];
        imageData[i+0] = imageData[i+2];
        imageData[i+2] = temp;
    }

	// テクスチャ登録に使用するイメージデータを作成する
	// RGBAで4byteずつ取得する
	image2Size = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 4;
	image2Data = new GLubyte [image2Size];

	// カラーキーを参照して特定色の場合はαで色を抜く
    for ( int i=0, index=0; i<(int)imageSize; i+=3, index++ )
    {
		image2Data[index*4+0] = imageData[i+0];
		image2Data[index*4+1] = imageData[i+1];
		image2Data[index*4+2] = imageData[i+2];
		image2Data[index*4+3] = 255;

		// 特定色の場合
		if(image2Data[index*4+0] == this->m_iColorKey[0]
			&& image2Data[index*4+1] == this->m_iColorKey[1]
			&& image2Data[index*4+2] == this->m_iColorKey[2]
			)
		{
			image2Data[index*4+3] = 0;
		}
	}

    //　ファイルを閉じる
    fclose(fp);

    return true;
}

/*! テクスチャ読み込み
*/
GLuint CBMPImage::load(const char *filename)
{
    if ( !ReadBMP(filename) )
	{
        return 0;
	}

	// テクスチャの作成
    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);

	// テクスチャ設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// テクスチャにイメージデータを登録する
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2Data);

	// 確保していたイメージデータの解放
    if ( imageData )
    {
        delete[] imageData;
        imageData = NULL;

		delete[] image2Data;
		image2Data = NULL;
    }

	// 登録したテクスチャIDを返す
    return ID;
}

/*! カラーキー（透明色）設定
*/
void CBMPImage::setColorKey(int iR, int iG, int iB)
{
	this->m_iColorKey[0] = iR;
	this->m_iColorKey[1] = iG;
	this->m_iColorKey[2] = iB;
}
