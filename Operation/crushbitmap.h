/*************************************************************************************
//
//  LICENSE INFORMATION
//
//  BCreator(tm)
//  Software for the control of the 3D Printer, "Creator"(tm)
//
//  Copyright 2011-2012 Creations, LLC
//  Creations(tm) and Creator(tm) are trademarks of Creations, LLC
//
//  This file is part of Creator
//
//    Creator is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Creator is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Creator .  If not, see <http://www.gnu.org/licenses/>.
//
//  The above copyright notice and this permission notice shall be
//    included in all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
*************************************************************************************/

#ifndef CRUSHBITMAP_H
#define CRUSHBITMAP_H

#include <QPixmap>
#include <QBitArray>
#include <QFile>


enum SupportType {st_CIRCLE, st_SQUARE, st_TRIANGLE, st_DIAMOND};

/******************************************************
SimpleSupport is used to store and render simple
support structures dynamically during slice decompression
******************************************************/
class SimpleSupport {
public:
	SimpleSupport(QPoint point, SupportType type=st_CIRCLE, int size = 10, int start=0, int end=0) {mPoint = point; mType=type; mSize=size; mStart=start; mEnd=end;}
	SimpleSupport(SupportType type=st_CIRCLE, int size = 32) {mPoint = QPoint(16,16); mType=type; mSize=size; mStart=0; mEnd=0;}
	~SimpleSupport() {}

	void streamOutSupport(QDataStream* pOut);
	void streamInSupport(QDataStream* pIn);

    void draw(QImage* pImg, QColor* pColor = nullptr);  // Render the support to the image
	void setType(SupportType type){mType = type;}
	void setPoint(QPoint point){mPoint = point;}
	void setSize(int size){mSize = size;}
	void setStart(int start){mStart = start;}
	void setEnd(int end){mEnd = end;}
	int getStart(){return mStart;}
	int getEnd(){return mEnd;}
	QPoint getPoint(){return mPoint;}
    QImage getCursorImage(QColor* pColor);

private:
	QPoint mPoint;
	SupportType mType;
	int mSize;
	int mStart;
	int mEnd;

};


/******************************************************
CrushedBitMap uses a bitstream compression technique to
reduce the amount of storage required for a monochrome
image where large areas of black and white pixels are 
typically grouped together.
******************************************************/
class CrushedPrintJob;
class CrushedBitMap {
public:
    CrushedBitMap() {mIndex = 0; uiWhitePixels=0;m_bIsBaseLayer=false; m_iWidth=0; m_iHeight=0;}
	CrushedBitMap(QImage* pImage);
	CrushedBitMap(QPixmap* pPixmap);
    ~CrushedBitMap(){}
    friend class CrushedPrintJob;

private:
	bool crushSlice(QImage* pImage);
	bool crushSlice(QPixmap* pPixmap);
	void inflateSlice(QImage* pImage, int xOffset = 0, int yOffset = 0, bool bUseNaturalSize = false);
	bool saveCrushedBitMap(const QString &fileName);
	void streamOutCMB(QDataStream* pOut);
	bool loadCrushedBitMap(const QString &fileName);
	void streamInCMB(QDataStream* pIn);
	uint getWhitePixels(){return uiWhitePixels;}
	QRect getExtents(){return mExtents;}
	int getWidth() {return m_iWidth;}
	void setWidth(int width){m_iWidth = width;}
	int getHeight() {return m_iHeight;}
	void setHeight(int height){m_iHeight = height;}
	void setIsBaseLayer(bool isBL){m_bIsBaseLayer=isBL;}
	bool isWhitePixel(QPoint qPoint);
	
	QBitArray mBitarray;
	int mIndex;
	uint uiWhitePixels;
	bool pixelIsWhite(QImage* pImage, unsigned uCurPos);
	void setWhiteImagePixel(QImage* pImage, unsigned uCurPos);	
	int computeKeySize(unsigned uData);
	void pushBits(int iValue, int iBits);
	int  popBits(int iBits);
	QRect mExtents;
	int m_iWidth, m_iHeight, m_xOffset, m_yOffset;
	bool m_bIsBaseLayer;
};

//start_edit_by_jinwg 20140807 for anti
class CrushedAntiBitMap
{
public:
	CrushedAntiBitMap() {mIndex = 0;uiWhitePixels=0; m_bIsBaseLayer=false; m_iWidth=0; m_iHeight=0;}
	CrushedAntiBitMap(QImage* pImage);
	CrushedAntiBitMap(QPixmap* pPixmap);
	~CrushedAntiBitMap(){}
	friend class CrushedPrintJob;

private:
	bool saveCrushedAntiBitMap(const QString &fileName);
	bool loadCrushedAntiBitMap(const QString &fileName);
	void streamOutCMB(QDataStream* pOut);
	void streamInCMB(QDataStream* pIn);
	
	void inflateSlice(QImage* pImage, int xOffset, int yOffset, bool bUseNaturalSize);
	bool crushSlice(QImage* pImage);
	bool crushSlice(QPixmap* pPixmap);
	uint getWhitePixels(){return uiWhitePixels;}
	void setWhitePixels(QImage *pImage);
    QRect getExtents(){return mExtents;}
	void AntiImageToByteArray(QImage* pImage);
	void AntiImageToByteArray(QPixmap* pPixmap);
	void ByteArrayToAntiImage(QImage* pImage, int xOffset, int yOffset, QByteArray *pBytearray);
	int getWidth() {return m_iWidth;}
	void setWidth(int width){m_iWidth = width;}
	int getHeight() {return m_iHeight;}
	void setHeight(int height){m_iHeight = height;}
	void setIsBaseLayer(bool isBL){m_bIsBaseLayer=isBL;}
	bool isWhitePixel(QPoint qPoint);
	QByteArray mBytearray;
	uint uiWhitePixels;
	quint32 mIndex;
	int m_iWidth, m_iHeight, m_xOffset, m_yOffset;
	bool m_bIsBaseLayer;
	QRect mExtents;

	quint32 mBytearraySize;
	
};
//end_edit_by_jinwg

/******************************************************
CrushedPrintJob manages all the crushed Bit Map image
slices that make up a print job.
******************************************************/
class CrushedPrintJob {
public:
	CrushedPrintJob();
	~CrushedPrintJob() {}

    void clearAll(int iLayers = 0);    // removes all slices and resets all variables


    int getTotalLayers();  // total layers including the base standoff offset layers
    uint getTotalWhitePixels() {return mTotalWhitePixels;} // returns all white pixels (fast)
    uint getTotalWhitePixels(int iFirst, int iLast); // sums the layer range of white pixels (slower)

	bool loadCPJ(QFile* pFile); // returns false if unknown version or opening error
	bool saveCPJ(QFile* pFile); // returns false if unable to write to file.
    bool saveCPJPrintModel(QFile *pFile);

    void setBase(int iBase) {mBase = iBase;}  // set the base standoff offset layers
    void setFilled(int iFilled) {mFilled = iFilled; if(mFilled>mBase)mFilled=mBase;} // Number of base offset layers where extents are filled
	int  getBase() {return mBase;}
	int  getFilled() {return mFilled;}

    void showSupports(bool bShow) {mShowSupports = bShow;}  // Set the support rendering flag
	bool renderingSupports() {return mShowSupports;}

    int getVersion(){return m_versionCPJ;}  // Version for file loads and saves
    QString getName(){return mName;}        // Short name for job
    QString getDescription(){return mDescription;}  // Job description
    QString getXYPixel(){return mXYPixel;}          // The xy pixel size in millimeters, for scaling purposes, set when sliced
    double getXYPixelmm(){return mXYPixel.toDouble();}
    QString getZLayer(){return mZLayer;}            // The z layer thickness in millimeters, for scaling purposes, set when sliced
    double getZLayermm(){return mZLayer.toDouble();}

	void setVersion(int s){m_versionCPJ= s;}
	void setName(QString s){mName = s;}
	void setDescription(QString s){mDescription = s;}
	void setXYPixel(QString s){mXYPixel = s;}
	void setZLayer(QString s){mZLayer = s;}
    void setSTLFiles(QList<QString>& fList){m_STLFiles = fList;}
    QList<QString> getSTLFiles(){return m_STLFiles;}

    // render the current slice (m_CurrentSlice) centered (shifted by Offsets) into pImage
    // if bUseNaturalSize, replace the pImage with one sized to this slice's size (offsets may cause clipping!)
    // inflates the raw image and then renders supports, filled base extents, etc.
	void inflateCurrentSlice(QImage* pImage, int xOffset = 0, int yOffset = 0, bool bUseNaturalSize = false);

    // attempts to replace the current slice with the crushed version of pImage stored at m_CurrentSlice.  Adjusts the job's width and height if needed
    bool crushCurrentSlice(QImage* pImage);

    // attempts to crushe and append pImage to the CBM array
    bool addImage(QImage* pImage);

    // Internal position index used for "current" function calls: m_CurrentSlice
    int getCurrentSlice() {return m_CurrentSlice;}
	void setCurrentSlice(int iSlice) {m_CurrentSlice = iSlice;}

    // Manage job supports
	void AddSupport(int iEndSlice, QPoint qCenter, int iSize = 10, SupportType eType=st_CIRCLE, int fastmode = true);
    bool DeleteSupport(int iSlice, QPoint qCenter, int iRadius = 0);
    void DeleteAllSupports(){mSupports.clear();}
	QSize GetSliceSize(){return QSize(m_Width,m_Height);}
    QImage GetSliceImage(int numberOfSlice);
    QString getPrintModel() { return mprintModel; }
    void setPrintModel(QString val) { mprintModel = val; }
    int CheckPrintModel(QString strMode);
private:
    CrushedBitMap* getCBMSlice(int i);  // gets the zero based index CBM
	CrushedAntiBitMap* getCBMSliceAnti(int i);
    bool isWhitePixel(QPoint qPoint, int iSlice = -1);

    // Job file load/save
	void streamInCPJ(QDataStream* pIn);
	void streamInCPJAnti(QDataStream* pIn);
	void streamOutCPJ(QDataStream* pOut);
	void streamOutCPJAnti(QDataStream* pOut);

    QList <CrushedBitMap> mSlices;   // Slices, not including base offset layers
    QList <CrushedAntiBitMap> mSlicesAnti;   // Slices, not including base offset layers
    QList <SimpleSupport> mSupports; // Supports to be rendered
    void addCBM(CrushedBitMap mCBM){mSlices.append(mCBM);}
    void addCBM(CrushedAntiBitMap mCBM){mSlicesAnti.append(mCBM);}
	uint mTotalWhitePixels;
	QString mVersion, mName, mDescription, mXYPixel, mZLayer;
    QString mprintModel, mReserved1, mReserved2, mReserved4, mReserved5;
	bool mShowSupports;
    qint32 mBase, mFilled;  // The number of base layers and the number of filled base layers
	CrushedBitMap mBaseLayer;
	CrushedAntiBitMap mBaseLayerAnti;
	int m_CurrentSlice;
	QRect mJobExtents;
	int m_Width, m_Height;

	int m_versionCPJ;
    QList<QString> m_STLFiles;
};

class SmartPrintJob{
public:
    SmartPrintJob(){}
    ~SmartPrintJob(){}
	static bool loadCPJ(QString sFile);
    static bool saveCPJNew(QString oldFile, QString newFile);
	static QList<QString> getCPJInfo();
    static QList<QString> getCPJAllInfo();
	static QList<QImage> getImageList();
	static QImage getOneImage(int nIndex);
	static void releaseCPJ();
    static int getNumImages();
    int checkIsNewSSJFile();
private:
	static CrushedPrintJob* m_pJob;
};

#endif // CRUSHBITMAP_H
