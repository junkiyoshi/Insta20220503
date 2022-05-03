#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetColor(0);
	ofSetLineWidth(1.5);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		this->radius_list[i] += this->speed_list[i];
		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
		}
	}
	
	for (int i = 0; i < 2; i++) {

		int random_radius = ((ofGetFrameNum() * 4 + i * 320) % 640) + ofRandom(-10, 10);
		int loop_count = random_radius < 120 ? ofMap(random_radius, 0, 120, 0, 10) : ofMap(random_radius, 120, 640, 10, 120);
		for (int k = 0; k < loop_count; k++) {

			int random_deg = ofRandom(360);

			auto location = glm::vec2(random_radius * cos(random_deg * DEG_TO_RAD), random_radius * sin(random_deg * DEG_TO_RAD));
			this->location_list.push_back(location);
			this->radius_list.push_back(1);
			this->speed_list.push_back(ofRandom(0.2, 1.5));
			this->max_radius_list.push_back(ofRandom(5, 30));
		}
	}

	this->line.clear();
	for (int i = 0; i < this->location_list.size(); i++) {

		this->line.addVertex(glm::vec3(this->location_list[i], 0));
		this->line.addColor(ofColor(0, ofMap(this->radius_list[i], 1, this->max_radius_list[i], 255, 30)));
	}

	for (int i = 0; i < this->line.getNumVertices(); i++) {
		
		for (int k = i + 1; k < this->line.getNumVertices(); k++) {

			auto distance = glm::distance(this->line.getVertex(i), this->line.getVertex(k));

			if (distance < 30) {

				this->line.addIndex(i);
				this->line.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->line.drawWireframe();
	for (int i = 0; i < this->location_list.size(); i++) {

		ofNoFill();
		ofDrawRectangle(this->location_list[i], 10, 10);

		ofFill();
		ofDrawCircle(this->location_list[i], 3);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}