#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxTuio.h"


#define CARD_MAX (53)

typedef enum{
    unoR = 0,
    unoG =10,
    unoB =20,
    unoY =30,
}UNO_COLOR;


typedef struct{
    UNO_COLOR color;
    int number;
}UNO_card;




//--------------------------------------------------------
class ofApp : public ofSimpleApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
    //TUIOの物体(マーカー)に関係するイベントを追加
    //物体の追加を検知
    void objectAdded(ofxTuioObject & tuioObject);
    //物体の削除を検知
    void objectRemoved(ofxTuioObject & tuioObject);
    //物体の状態の更新を検知
    void objectUpdated(ofxTuioObject & tuioObject);
    
    //TUIOのカーソル(タッチポイントなど)に関係するイベント
    //カーソルの追加を検知
    void tuioAdded(ofxTuioCursor & tuioCursor);
    //カーソルの削除を検知
    void tuioRemoved(ofxTuioCursor & tuioCursor);
    //カーソルの状態の更新を検知
    void tuioUpdated(ofxTuioCursor & tuioCursor);
    
    
    vector<UNO_card> detected_cards;
    ofImage cardImgs[52+1];
    float cardY;
    float cardMove =0;
    
    ofVec2f pos;
    
    
private:
    //TUIOのクライアントのインスタンス化
    myTuioClient tuio;
    //ログの出力用
    string log;
    
    //表示する画像
    ofImage myImage;
};

#endif