#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->number_of_targets = 150;
	for (int i = 0; i < this->number_of_targets; i++) {

		this->targets.push_back(glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
		glm::vec3  color = glm::vec3(1.0, 1.0, 1.0);
		int color_type = i % 3;
		switch (color_type) {
		case 0:
			color = glm::vec3(1.0, 0.0, 0.0);
			break;
		case 1:
			color = glm::vec3(0.0, 1.0, 0.0);
			break;
		case 2:
			color = glm::vec3(0.0, 0.0, 1.0);
			break;
		}
		this->colors.push_back(color);
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int i = 0; i < this->number_of_targets; i++) {

		int gap = ofRandom(-80, 80);
		int speed = ofRandom(5, 10);
		int x = ((int)ofRandom(ofGetWidth()) + ofGetFrameNum() * speed) % ofGetWidth();
		int y = gap + sin(x * 0.005) * ofGetHeight() * 0.4 + ofGetHeight() * 0.5;
		this->targets[i] = glm::vec2(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &this->targets[0].x, this->number_of_targets);
	this->shader.setUniform3fv("colors", &this->colors[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(1280, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}