#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
// uniform vec2 u_mouse;
// uniform float u_time;
uniform sampler2D texture;

void main(){
    vec2 st=gl_FragCoord.xy/u_resolution.xy;
    
    float centerOffset=-.5;
    vec2 uvCentered=st+centerOffset;
    
    vec2 uvNew=uvCentered*(.9+.5*vec2(4./3.,1.)*length(uvCentered))-centerOffset;//bar - centerOffset;
    
    vec3 color=texture2D(texture,gl_TexCoord[0].xy).rgb;
    
    int t=int(uvNew.y*u_resolution.y)/(int(u_resolution.y)/200);
    float q=mod(float(t),2.);
    float brightness;
    if(q==0.){
        brightness=1.;
    }else{
        brightness=.5;
    }
    
    // =t==0.?1.:.5;
    
    if(uvNew.x>=0.&&uvNew.x<=1.&&uvNew.y>=0.&&uvNew.y<=1.){
        color=texture2D(texture,uvNew).rgb;
        if(color==vec3(1.)){
            color=brightness*vec3(.4039,.9216,.5137);
        }else{
            color+=brightness*vec3(.0706,.1647,.0902);
        }
    }
    else{
        color=vec3(.051,.4078,.4314);
    }
    
    gl_FragColor=vec4(color,1.);
    //gl_FragColor=texture2D(texture,gl_TexCoord[0].xy);
    
}