     #include "ofApp.h"

void ofApp::setup(){
    //TUIOに関連するイベントリスナーの追加
    ofAddListener(tuio.objectAdded,this,&ofApp::objectAdded);
    ofAddListener(tuio.objectRemoved,this,&ofApp::objectRemoved);
    ofAddListener(tuio.objectUpdated,this,&ofApp::objectUpdated);
    ofAddListener(tuio.cursorAdded,this,&ofApp::tuioAdded);
    ofAddListener(tuio.cursorRemoved,this,&ofApp::tuioRemoved);
    ofAddListener(tuio.cursorUpdated,this,&ofApp::tuioUpdated);
    
    //フレームレート設定
    ofSetFrameRate(60);
  
    ofBackground(255);
    
    //ポート番号3333で、TUIOの通信開始
    tuio.start(3333);
    
    //ログのテキストを空に
    log="";
    //画像ファイルを読み込み
    //myImage.load("hachi.png");
    
    for (int i = 1; i <= 52; i++) {
        cardImgs[i].load(ofToString(i) + ".jpg");
    }
}

void ofApp::update(){
    //TUIOのメッセージを受信
    tuio.getMessage();
}

void ofApp::draw(){
    
    
//    //オブジェクトのリストを取得
//    list<ofxTuioObject*> objectList = tuio.getTuioObjects();
//    //リスト操作のためのイテレータを準備
//    list<ofxTuioObject*>::iterator tobj;
//    //全てのオブジェクトをイテレータで操作
//    for (tobj=objectList.begin(); tobj != objectList.end(); tobj++) {
//        //物体を取得
//        ofxTuioObject *blob = (*tobj);
//        //座標を記録
//        glPushMatrix();
//        //座標を移動
//        
//        int idNumber = blob->getFiducialId();
//        //glTranslatef(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), 0.0);
//        glTranslatef(100, idNumber*20, 0.0);
//        
//        int color = idNumber/10;
//        int num = idNumber%10;
//        
//        
//        
//        //ID番号を表示
//        ofDrawBitmapString("id = " + ofToString( idNumber , 0), -64, 80);
//        //回転
//glRotatef(blob->getAngleDegrees(), 0.0, 0.0, 1.0);
//ofSetColor(255, 255, 255);
//        //画像を描画
//        
      ofSetColor(255*fVNumber/11.f, 255, 255);
    //ofSetColor(255*idNumber/11.f, 255, 255);
//        
        myImage.draw(-64, -64,32,32);
//        //座標を復帰
//        glPopMatrix();
//    }
    
    
    
    //カーソルの状態を表示
   // tuio.drawCursors();
    //オブジェクトの状態を表示
   // tuio.drawObjects();
    //ログを表示
    ofSetHexColor(0xffffff);
    ofDrawBitmapString(log, 20, 20);
    
    int card_cnt = detected_cards.size();
    
    for (int i=0; i<card_cnt; i++) {
        UNO_COLOR c = detected_cards[i].color;
        int n = detected_cards[i].number;
        ofDrawBitmapString("color = " + ofToString( c,2) + " / number = " + ofToString( n,2), 30, 60 + 20*i);
        myImage.draw(ofGetWidth()/2,ofGetHeight()/2,200,200);
    }
    
    for(int i = 0; i < detected_cards.size(); i++){
        
        if (cardMove > cardMove-150) {
            cardMove--;
            pos.x += cardMove;
            pos.y += cardMove+3;
        }
        ofLog() << detected_cards[i].number ;
        if ((detected_cards[i].number >= 1) && (detected_cards[i].number <=52)) {
            cardImgs[detected_cards[i].number].draw(729, i * 150+cardMove, 231, 150);
        }
        
        

        
    }
    
    
}

void ofApp::keyPressed  (int key){
}
void ofApp::mouseMoved(int x, int y ){
}
void ofApp::mouseDragged(int x, int y, int button){
}
void ofApp::mousePressed(int x, int y, int button){
}
void ofApp::mouseReleased(){
    
    
}

void ofApp::objectAdded(ofxTuioObject & tuioObject){
    
    UNO_card new_card;
    int color = tuioObject.getFiducialId()/CARD_MAX;
    int num = tuioObject.getFiducialId()%CARD_MAX;
    
    new_card.color = (UNO_COLOR)color;
    new_card.number = num;
    
    
    //重複チェック
    bool isAccepable = true;
    
    for (int i=0; i<detected_cards.size(); i++) {
        UNO_COLOR c = detected_cards[i].color;
        int n = detected_cards[i].number;
        
        if (c==new_card.color) {
            if (n==new_card.number) {
                isAccepable = false;
            }
        }
    }
 
    if ( isAccepable ) {
        detected_cards.push_back(new_card);
    }
    
    if (detected_cards.size() > 4) {
        detected_cards.erase(detected_cards.begin());
    }
 
    //マーカー追加
    myImage.draw(ofGetWidth()/2,ofGetHeight()/2);
    
    log = " new object: " + ofToString(tuioObject.getFiducialId())+
    " X: "+ofToString(tuioObject.getX())+
    " Y: "+ofToString(tuioObject.getY())+
    " angle: "+ofToString(tuioObject.getAngleDegrees()) +
    " color: "+ofToString(color);
    
    
    
}



void ofApp::objectRemoved(ofxTuioObject & tuioObject){
//    //マーカー削除
//    log = " object removed: " + ofToString(tuioObject.getFiducialId())+
//    " X: "+ofToString(tuioObject.getX())+
//    " Y: "+ofToString(tuioObject.getY())+
//    " angle: "+ofToString(tuioObject.getAngleDegrees());
}
void ofApp::objectUpdated(ofxTuioObject & tuioObject){
//    //マーカーの状態更新
//    log = " object updated: " + ofToString(tuioObject.getFiducialId())+
//    " X: "+ofToString(tuioObject.getX())+
//    " Y: "+ofToString(tuioObject.getY())+
//    " angle: "+ofToString(tuioObject.getAngleDegrees());
}
void ofApp::tuioAdded(ofxTuioCursor & tuioCursor){
//    //カーソル追加
//    log = " new cursor: " + ofToString(tuioCursor.getFingerId())+
//    " X: "+ofToString(tuioCursor.getX())+
//    " Y: "+ofToString(tuioCursor.getY());
}
void ofApp::tuioRemoved(ofxTuioCursor & tuioCursor){
//    //カーソル削除
//    log =  " cursor removed: " + ofToString(tuioCursor.getFingerId())+
//    " X: "+ofToString(tuioCursor.getX())+
//    " Y: "+ofToString(tuioCursor.getY());
}
void ofApp::tuioUpdated(ofxTuioCursor & tuioCursor){
//    //カーソル状態更新
//    log =  " cursor updated: " + ofToString(tuioCursor.getFingerId())+
//    " X: "+ofToString(tuioCursor.getX())+
//    " Y: "+ofToString(tuioCursor.getY());
}