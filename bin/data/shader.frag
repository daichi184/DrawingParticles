//http://ayumu-nagamatsu.com/archives/286/
#version 120
//precision mediump float;

//--------------------------------------------------------------
// common
//--------------------------------------------------------------
uniform vec2 resolution;
uniform sampler2DRect texture; // 型に注意。sampler2Dではダメ。
uniform float time;

varying vec2 vTexCoord;

//--------------------------------------------------------------
// カラー空間
//--------------------------------------------------------------
void main() {
    vec4 samplerColor = texture2DRect(texture, vTexCoord);

    gl_FragColor = samplerColor;
    
}










