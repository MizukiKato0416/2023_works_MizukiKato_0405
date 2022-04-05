xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 154;
 -4.51144;-5.52716;-2.01080;,
 -2.09040;-4.50204;-2.24767;,
 -1.34442;-19.56273;-2.40950;,
 -3.11588;-19.62057;-2.29689;,
 0.07740;-9.62458;-2.01080;,
 0.18296;-19.56273;-2.01080;,
 -3.11588;-19.62057;-2.29689;,
 -1.34442;-19.56273;-2.40950;,
 -1.34442;-19.56273;1.80958;,
 -3.11588;-19.62057;1.69696;,
 -3.11588;-19.62057;1.69696;,
 -1.34442;-19.56273;1.80958;,
 -2.09040;-4.50204;1.64779;,
 -4.51144;-5.52716;1.41090;,
 0.18296;-19.56273;1.41090;,
 0.07740;-9.62458;1.41090;,
 -4.51144;-5.52716;1.41090;,
 -2.09040;-4.50204;1.64779;,
 -2.09040;-4.50204;-2.24767;,
 -4.51144;-5.52716;-2.01080;,
 -4.51144;-5.52716;-2.01080;,
 -3.11588;-19.62057;-2.29689;,
 0.15750;4.23407;-3.96519;,
 3.41273;4.23406;-3.96519;,
 3.41273;-10.78431;-3.46355;,
 0.15750;-14.19432;-2.27738;,
 0.15750;-14.19432;1.79691;,
 3.41273;-10.78431;2.98308;,
 3.41273;5.45717;2.91281;,
 0.15750;5.45717;2.91281;,
 0.15750;5.45717;2.91281;,
 3.41273;5.45717;2.91281;,
 3.41273;4.23406;-3.96519;,
 0.15750;4.23407;-3.96519;,
 0.15750;4.23407;-3.96519;,
 0.15750;-14.19432;-2.27738;,
 0.15750;-14.19432;1.79691;,
 3.41273;4.23406;-3.96519;,
 3.41273;-10.78431;2.98308;,
 3.41273;-10.78431;-3.46355;,
 -1.45514;-19.78677;-3.15735;,
 2.30672;-19.78678;-3.15735;,
 1.94363;-24.15576;-2.60260;,
 -1.09208;-24.15576;-2.60260;,
 -1.09208;-24.15576;-2.60260;,
 1.94363;-24.15576;-2.60260;,
 1.94363;-24.15576;2.03586;,
 -1.09208;-24.15576;2.03586;,
 -1.09208;-24.15576;2.03586;,
 1.94363;-24.15576;2.03586;,
 2.30672;-19.78678;2.59058;,
 -1.45514;-19.78677;2.59058;,
 -1.45514;-19.78677;2.59058;,
 -1.45514;-19.78677;-3.15735;,
 -1.09208;-24.15576;-2.60260;,
 2.30672;-19.78678;-3.15735;,
 2.30672;-19.78678;2.59058;,
 1.94363;-24.15576;-2.60260;,
 -4.09735;-14.61593;2.64923;,
 -4.09735;-14.61593;-3.52626;,
 -4.09735;-15.62416;-3.52626;,
 -4.09735;-15.62416;2.64923;,
 -4.09113;-14.60587;-3.52441;,
 1.04024;-9.18515;-2.95837;,
 1.74512;-9.89184;-2.95837;,
 -3.47658;-15.31256;-3.52441;,
 -4.09113;-15.60019;-3.52441;,
 -4.08891;-14.61652;-3.52441;,
 1.74512;-20.31424;-3.15400;,
 1.04021;-21.02092;-3.15400;,
 -4.09113;-15.60174;2.66289;,
 1.04021;-21.10681;2.66289;,
 1.74512;-20.40014;2.66289;,
 -4.09215;-14.63197;2.66291;,
 -4.09113;-14.60508;2.66289;,
 -3.47655;-15.22743;2.66291;,
 1.74512;-9.80669;2.05935;,
 1.04021;-9.10002;2.05935;,
 -0.73424;-15.18563;1.45300;,
 -0.73424;-15.18563;-1.96871;,
 3.40929;-10.79282;-3.49729;,
 3.40929;-10.79282;2.98159;,
 2.59405;-11.29958;-2.91647;,
 2.59405;-11.29958;0.09041;,
 2.17874;-21.37954;0.09041;,
 2.17874;-21.37954;-2.91647;,
 0.41175;-21.46741;1.27761;,
 1.66868;-21.37953;-1.05837;,
 1.84575;-11.29960;-1.32347;,
 -0.66615;-12.80498;1.51004;,
 0.41175;-21.46741;-2.00031;,
 -0.66615;-12.80498;-1.99154;,
 2.32049;-11.29960;-1.00164;,
 1.66868;-21.37953;-0.77212;,
 -6.13474;4.84640;-5.96813;,
 4.70171;1.18246;-3.73982;,
 2.79829;-22.82836;-3.94936;,
 -0.98823;-24.55858;-2.65689;,
 -6.13479;4.84588;-5.91178;,
 -0.98833;-24.55902;-2.60068;,
 2.79829;-22.82882;-3.89296;,
 4.70171;1.18204;-3.68340;,
 -2.79410;-23.92819;-3.37867;,
 -1.22365;-30.00033;-3.37867;,
 -1.22365;-30.00033;2.69347;,
 -2.79410;-24.21156;2.69347;,
 2.78439;-24.21156;2.69347;,
 1.17707;-30.00033;2.69347;,
 1.17707;-30.00033;-3.37867;,
 2.78439;-23.92819;-3.37867;,
 1.36205;-35.58795;-5.37347;,
 1.19582;-38.03203;-3.54240;,
 -1.20553;-38.03203;-3.54240;,
 -1.37177;-35.58795;-5.37347;,
 -1.37177;-35.58795;-5.37347;,
 -1.20553;-38.03203;-3.54240;,
 -2.77767;-24.02999;-2.97225;,
 -2.79410;-23.94031;-3.31016;,
 2.78439;-23.94031;-3.31016;,
 2.89587;-23.88055;-2.97225;,
 1.19582;-38.03203;-3.54240;,
 1.36205;-35.58795;-5.37347;,
 1.36205;-35.58795;-5.37347;,
 -1.37177;-35.58795;-5.37347;,
 -2.78023;-24.15441;2.71099;,
 -1.15282;-30.00033;2.71099;,
 -1.15282;-37.05747;4.79370;,
 -1.31176;-18.07994;7.53416;,
 -1.31176;-18.07994;7.53416;,
 -1.15282;-37.05747;4.79370;,
 1.14311;-37.05747;4.79370;,
 1.30207;-18.07994;7.53416;,
 1.30207;-18.07994;7.53416;,
 1.14311;-37.05747;4.79370;,
 1.14311;-30.00033;2.71099;,
 2.77052;-24.15441;2.71099;,
 2.77052;-24.15441;2.71099;,
 -2.78023;-24.15441;2.71099;,
 1.34314;-17.97411;7.33282;,
 2.10411;-10.49131;14.84712;,
 1.34314;-28.83611;13.00321;,
 1.34314;-37.01448;4.63846;,
 2.10411;-10.49131;14.84712;,
 -2.03164;-10.49131;14.84712;,
 -1.27069;-28.83611;13.00321;,
 1.34314;-28.83611;13.00321;,
 -2.03164;-10.49131;14.84712;,
 -1.27069;-17.97411;7.33282;,
 -1.27069;-37.01448;4.63846;,
 -1.27069;-28.83611;13.00321;,
 1.34314;-17.97411;7.33282;,
 -1.27069;-17.97411;7.33282;,
 -1.27069;-37.01448;4.63846;,
 1.34314;-37.01448;4.63846;;
 
 43;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;11,14,15,12;,
 4;16,17,18,19;,
 4;16,20,21,9;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,34,35,36;,
 4;37,31,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,47;,
 4;55,56,46,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;118,122,123,117;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,136,137,127;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 4;146,139,150,151;,
 4;152,153,140,149;;
 
 MeshMaterialList {
  5;
  43;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  4,
  4,
  4,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.432800;0.432800;0.432800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.065600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.031200;0.031200;0.031200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.248000;0.248000;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.615200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  46;
  -0.081849;0.009841;-0.996596;,
  0.060659;0.010224;-0.998106;,
  0.201935;0.010399;-0.979344;,
  0.032634;-0.999467;-0.000000;,
  0.201930;0.010398;0.979345;,
  -0.081855;0.009838;0.996596;,
  0.060653;0.010222;0.998107;,
  -0.130293;-0.061295;-0.989579;,
  -0.147281;-0.025241;0.988773;,
  -0.000000;-0.125963;-0.992035;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-0.125956;0.992036;,
  -1.000000;0.000000;0.000000;,
  0.055184;0.051412;-0.997152;,
  0.049177;-0.017584;-0.998635;,
  -0.000008;-0.000010;1.000000;,
  0.056755;0.056346;0.996797;,
  0.727446;-0.686165;-0.000000;,
  0.999152;-0.041167;-0.000000;,
  0.817332;0.050641;0.573937;,
  0.526596;0.022535;-0.849817;,
  -0.029428;-0.082167;-0.996184;,
  0.029402;0.082161;0.996185;,
  -0.389910;0.920853;0.000000;,
  -0.995133;-0.098540;0.000000;,
  0.000001;0.984554;-0.175083;,
  1.000000;0.000000;0.000000;,
  -0.996565;-0.082814;0.000000;,
  0.996564;-0.082821;-0.000000;,
  0.965126;-0.261716;-0.005971;,
  -0.966630;-0.256110;-0.005842;,
  0.000000;-0.231702;-0.972787;,
  0.000000;-0.599583;-0.800313;,
  -0.992975;-0.116601;-0.020134;,
  0.978172;-0.107338;-0.177925;,
  0.954832;-0.122306;0.270809;,
  -0.954831;-0.122306;0.270812;,
  0.000000;-0.142923;0.989734;,
  -0.999297;-0.017355;-0.033244;,
  0.999296;-0.017355;-0.033245;,
  0.000000;-0.100010;0.994986;,
  0.000000;-0.433543;0.901133;,
  0.000000;0.174428;-0.984670;,
  0.000000;0.621829;-0.783153;,
  0.000000;0.708591;-0.705620;,
  0.000000;-0.715028;0.699096;;
  43;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;5,6,6,5;,
  4;6,4,4,6;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;25,25,25,25;,
  4;12,12,12,12;,
  4;26,26,26,26;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;30,30,30,30;,
  4;29,29,29,29;,
  4;31,32,32,31;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;42,31,31,42;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;35,35,35,35;,
  4;43,43,43,43;,
  4;39,39,39,39;,
  4;40,40,41,41;,
  4;38,38,38,38;,
  4;44,44,44,44;,
  4;45,45,41,41;;
 }
 MeshTextureCoords {
  154;
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
