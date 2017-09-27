
#include "ofApp.h"

void ofApp::setup(){
    
	ofSetVerticalSync(true);
    //ofEnableDepthTest();
	ofEnableAlphaBlending();

	selectedImage = NULL;
    
    //Looped Music
    sample.load("loop.aif");
    sample.setVolume(0.06);
    sample.setLoop(true);
    
    //Select MenuBar Sound
    sample_pop.load("pop.aif");
    sample_pop.setVolume(1);
    sample_pop.setLoop(false);
    
    //Starting Music
    sample_mac.load("start.aif");
    sample_mac.setVolume(0.1);
    sample_mac.setLoop(false);
    sample_mac.play();
    
    
    //I should have used a for loop to load the images.
    pictures[0].load("images/1.png");
    pictures[1].load("images/2.png");
    pictures[2].load("images/3.png");
    pictures[3].load("images/4.png");
    pictures[4].load("images/5.png");
    pictures[5].load("images/6.png");
    pictures[6].load("images/7.png");
    pictures[7].load("images/8.png");
    pictures[8].load("images/9.png");
    pictures[9].load("images/10.png");
    pictures[10].load("images/11.png");

    cur_music = false;
    cur_help = false;
    
}

void ofApp::update(){}

void ofApp::draw(){
    
    ofBackground(245,245,255);
	ofFill();
    ofSetColor(0);
    
    //Display Menu Text
    ofDrawBitmapString("Add  Del  Mag+ Mag-  Z+   Z- Rot+ Rot- Save Music Help", 14, 60);
    
    //Check if menu button pressed
    if(cur_help){
        ofDrawBitmapString("Help", 14 , 155);
        ofDrawBitmapString("____", 14 , 160);
        ofDrawBitmapString("R, r -> Reset Rotation", 14 , 175);
        ofDrawBitmapString("Up_Arrow -> Zoom In", 14 , 190);
        ofDrawBitmapString("Down_Arrow -> Zoom Out", 14 , 205);
        ofDrawBitmapString("Left_Arrow -> Rotate Left", 14 , 220);
        ofDrawBitmapString("Right_Arrow -> Rotate Right", 14 , 235);
        ofDrawBitmapString("D, d -> Delete", 14 , 250);
        ofDrawBitmapString("Drag Mouse to position image", 14 , 265);
        ofDrawBitmapString("Made with <3, coffee and a lot of procrastination", 14 , 295);
        ofDrawBitmapString(" - Siddharth Kulkarni", 14 , 310);
    }
    
    //Loop through images to draw
    for (int i = 0; i < images.size(); i++ ) {
        images[i]->draw();
    }
    
    //Trying to make 'X' icon, but I messed it up
    if(selectedImage && selectedImage->rot == 0){
        
        ofFill();
        ofSetColor(2, 119, 189);
       //cross.set(selectedImage->trans.x + selectedImage->image.getWidth()/4.0 - 20, selectedImage->trans.y - selectedImage->image.getHeight()/4.0 - 20, 40, 40);
       //ofDrawRectangle(cross);
        cross.x = selectedImage->trans.x + selectedImage->image.getWidth()/4.0 - 20 - 20;
        cross.y = selectedImage->trans.y - selectedImage->image.getHeight()/4.0 - 20 + 28;
        cross.width = 30;
        cross.height = 30;
        ofDrawRectRounded(cross,20);
        
        ofFill();
        ofSetLineWidth(3);
        ofSetColor(255);
        ofDrawLine(selectedImage->trans.x + selectedImage->image.getWidth()/4.0 - 10 - 25, selectedImage->trans.y - selectedImage->image.getHeight()/4.0 - 10 + 28 - 5, selectedImage->trans.x + selectedImage->image.getWidth()/4.0 + 10 - 25, selectedImage->trans.y - selectedImage->image.getHeight()/4.0 + 10 + 28 - 5);
        ofDrawLine(selectedImage->trans.x + selectedImage->image.getWidth()/4.0 - 10 - 25, selectedImage->trans.y - selectedImage->image.getHeight()/4.0 + 10 + 23, selectedImage->trans.x + selectedImage->image.getWidth()/4.0 + 10 - 25 , selectedImage->trans.y - selectedImage->image.getHeight()/4.0 - 10 + 25 - 2);
        
       /* //2 Arrows for Cross
        
        ofDrawLine(selectedImage->image.getWidth()/2.0 - 10 , -selectedImage->image.getHeight()/2.0 - 10, selectedImage->image.getWidth()/2.0 + 10, -selectedImage->image.getHeight()/2.0 + 10);
        ofDrawLine(selectedImage->image.getWidth()/2.0 + 10, -selectedImage->image.getHeight()/2.0 - 10, selectedImage->image.getWidth()/2.0 - 10, -selectedImage->image.getHeight()/2.0 + 10); */
        
    }
    
    //drawing menu icons
    for(int i=0;i<11;i++){
        pictures[i].draw(i*40 + 10,10);
    }
    
}

//exit method
void ofApp::exit() {
	for (int i = 0; i < images.size(); i++) {
		delete images[i];
	}
    sample.stop();
}

//keyPress
void ofApp::keyPressed(int key) {
	switch (key) {
     
     case OF_KEY_LEFT:
            if(selectedImage)
                selectedImage->rot-=5;
            break;
     case OF_KEY_RIGHT:
            if(selectedImage)
                selectedImage->rot+=5;
            break;
     case OF_KEY_UP:
            if(selectedImage)
                selectedImage->scale.x+=0.1;
                selectedImage->scale.y+=0.1;
            break;
     case OF_KEY_DOWN:
            if(selectedImage)
                selectedImage->scale.x-=0.1;
                selectedImage->scale.y-=0.1;
            break;
     case 'D':
     case 'd':
        if (selectedImage) {
            images.erase(images.begin() + images.size()-1);
            selectedImage->bSelected = false;
            selectedImage = NULL;
        }
        break;
        case 'R':
        case 'r':
            if (selectedImage) {
                selectedImage->rot = 0;
            }
            break;
	}
}

//keyReleased
void ofApp::keyReleased(int key) {}

//mouseMoved
void ofApp::mouseMoved(int x, int y ){}

//MouseDragged
void ofApp::mouseDragged(int x, int y, int button) {
    
    //For changing position of selected Image
    if(selectedImage){
        selectedImage->trans.x = x;
        selectedImage->trans.y = y;
    }
}

//mousePressed
void ofApp::mousePressed(int x, int y, int button){
    
    int index_i=-1;
    
    if(y>=10 && y<=42 && x>=10 && x<=440){
        
        index_i = (x-10)/40;
        
        //if(index_i!=10)
            sample_pop.play();
        
        //delete image
        if(index_i == 1 and selectedImage){
            images.erase(images.begin() + images.size()-1);
            selectedImage->bSelected = false;
            selectedImage = NULL;
        }
        
        //add Image
        if(index_i == 0){
           
            ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an image");
            
            //Check if the user opened a file
            if (openFileResult.bSuccess){
                
                //User selected a file
                
                //We have a file, check it and process it
                processOpenFileSelection(openFileResult);
                
            }else {
                cout<<"User hit cancel\n";
            }
            
        }
        
        //Zoom in
        if(index_i == 2 && selectedImage){
            selectedImage->scale.x+=0.05;
            selectedImage->scale.y+=0.05;
        }
        
        //Zoom out
        if(index_i == 3 && selectedImage){
            selectedImage->scale.x-=0.05;
            selectedImage->scale.y-=0.05;
        }
        
        //layer up
        if(index_i == 4 && selectedImage){
            int j=-1;
            for(int i=0;i<images.size();i++){
                if(images[i]->bSelected == true){
                    j = i;
                }
            }
            if(j!=images.size()-1){
                Image *temp = new Image();
                temp = images[j+1];
                images[j+1] = images[j];
                images[j] = temp;
            }
        }
        
        //layer down
        if(index_i == 5 && selectedImage){
            int j=-1;
            for(int i=0;i<images.size();i++){
                if(images[i]->bSelected == true){
                    j = i;
                }
            }
            if(j!=0){
                Image *temp = new Image();
                temp = images[j-1];
                images[j-1] = images[j];
                images[j] = temp;
            }
        }
        
        //rotate right
        if(index_i == 6 && selectedImage){
            selectedImage->rot+=15;
        }
        
        //rotate left
        if(index_i == 7 && selectedImage){
            selectedImage->rot-=15;
        }
        
        //downloadImage
        if(index_i == 8 && !selectedImage && !cur_help){
            if(images.size()!=0){
                // ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofGetTimestampString() + "." + ofToLower(originalFileExtension), "Save your file");
                ofImage screen_shot;
                screen_shot.grabScreen(0, 62, ofGetWidth(), ofGetHeight() - 62);
                //screen_shot.save(ofGetTimestampString() + "." + ofToLower(originalFileExtension));
                screen_shot.save("screenshot.png");
            }
        }
        
        //play music
        if(index_i == 9){
            cur_music=!cur_music;
            if(cur_music)
                sample.play();
            else
                sample.stop();
        }
        
        //help
        if(index_i == 10){
            cur_help = !cur_help;
            //sample_help.play();
           
        }
        return;
    }
    
	renderSelection();
	processSelection(x, y);
    if(selectedImage){
        if(cross.inside(x,y)){
            images.erase(images.begin() + images.size()-1);
            selectedImage->bSelected = false;
            selectedImage = NULL;
        }
    }
    
    
}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
    
    ofFile file (openFileResult.getPath());
    
    if (file.exists()){
        
        //The file exists - now checking the type via file extension
        string fileExtension = ofToUpper(file.getExtension());
        
        //We only want images
        if (fileExtension == "JPG" || fileExtension == "PNG") {
            
            ofImage temp;
            temp.load(file);
            
            //Load the selected image
            Image *imageObj = new Image();
            imageObj->trans.x = ofGetWindowWidth()/2.0;
            imageObj->trans.y = ofGetWindowHeight()/2.0;
            imageObj->image = temp;
            images.push_back(imageObj);
            
        }else{
            cout<<"incorrect file type";
        }
    }
    
}

void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}

// Simple file drag and drop implementation.
void ofApp::dragEvent(ofDragInfo dragInfo){
	Image *imageObj = new Image();
    imageObj->trans.x = dragInfo.position.x;
    imageObj->trans.y = dragInfo.position.y;
	//imageObj->trans = cam.screenToWorld(dragInfo.position);
    //cout<<"\n"<<dragInfo.files[0];
	if (imageObj->image.load(dragInfo.files[0]) == true)
		images.push_back(imageObj);
	else {
		cout << "Can't load image: " << dragInfo.files[0] << endl;
		delete imageObj;
	}
}

void ofApp::renderSelection() {
	
	ofBackground(0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (int i = 0; i < images.size(); i++) {
		images[i]->draw(true, i);
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ofApp::processSelection(int x, int y) {
    
	unsigned char res[4];
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

	if (selectedImage) {
		selectedImage->bSelected = false;
		selectedImage = NULL;
	}
    
	if (res[0] > 0 && res[0] <= images.size()) {
        
		Image *image = images[res[0] - 1];
		image->bSelected = true;
		selectedImage = image;
	
    }
}

Image::Image()
{
	trans.x = 0;
	trans.y = 0;
	scale.x = 0.5;
	scale.y = 0.5;
	rot = 0;
	bSelected = false;
}

void Image::draw(bool bSelectMode, int index) {
	ofPushMatrix();
	ofTranslate(trans);
	ofScale(scale);
	ofRotate(rot);

	// if drawing image normally
	if(!bSelectMode) {

		// if selected, draw box
        ofSetColor(255, 255, 255, 255);
        image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
        
		if (bSelected) {
            
            //outer box
			ofNoFill();
			ofSetColor(3, 169, 244, 50);
			ofSetLineWidth(2);
			ofDrawRectangle(-image.getWidth() / 2.0, -image.getHeight() / 2.0, image.getWidth(), image.getHeight());
            
           /* //Circle Cross
            ofFill();
            ofSetColor(2, 119, 189);
            ofDrawCircle(+image.getWidth()/2.0, -image.getHeight()/2.0, 25);
            ofSetColor(255,255,255); */
            
            
        }
		
	
    }
    
	//
	// else if drawing to test selection
	//
    
	else {
		ofFill();
		ofSetColor(index + 1, 0, 0);
		ofDrawRectangle(-image.getWidth() / 2.0, -image.getHeight() / 2.0,
			image.getWidth(), image.getHeight());
	}
	ofPopMatrix();
}

