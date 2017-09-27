#pragma once

#include "ofMain.h"

class Image {

	public:
		Image();
		ofVec2f trans, scale;
		float	rot;
		bool	bSelected;
		ofImage image;
		void	draw(bool bSelectMode = false, int index = 0);
        string myPath;
};



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void renderSelection();
		void processSelection(int x, int y);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void processOpenFileSelection(ofFileDialogResult openFileResult);
    
    

	private:
		vector<Image *> images;
		Image *selectedImage;
        ofRectangle cross;
        ofSoundPlayer sample, sample_pop, sample_mac, sample_help;
        ofImage pictures[11];
    
        string originalFileExtension;
    
        bool cur_music;
        bool cur_help;
};
