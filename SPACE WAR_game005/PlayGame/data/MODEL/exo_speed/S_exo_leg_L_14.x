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
 150;
 4.58204;-5.12485;-1.73465;,
 3.18648;-19.21828;-2.02074;,
 1.41504;-19.16044;-2.13335;,
 2.16101;-4.09973;-1.97152;,
 -0.11234;-19.16044;-1.73465;,
 -0.00678;-9.22228;-1.73465;,
 3.18648;-19.21828;-2.02074;,
 3.18648;-19.21828;1.97311;,
 1.41504;-19.16044;2.08573;,
 1.41504;-19.16044;-2.13335;,
 3.18648;-19.21828;1.97311;,
 4.58204;-5.12485;1.68705;,
 2.16101;-4.09973;1.92394;,
 1.41504;-19.16044;2.08573;,
 -0.00678;-9.22228;1.68705;,
 -0.11234;-19.16044;1.68705;,
 4.58204;-5.12485;1.68705;,
 4.58204;-5.12485;-1.73465;,
 2.16101;-4.09973;-1.97152;,
 2.16101;-4.09973;1.92394;,
 3.18648;-19.21828;-2.02074;,
 4.58204;-5.12485;-1.73465;,
 -0.08688;4.63638;-3.68904;,
 -0.08688;-13.79202;-2.00123;,
 -3.34212;-10.38201;-3.18740;,
 -3.34212;4.63637;-3.68904;,
 -0.08688;-13.79202;2.07306;,
 -0.08688;5.85948;3.18896;,
 -3.34213;5.85948;3.18896;,
 -3.34212;-10.38201;3.25923;,
 -0.08688;5.85948;3.18896;,
 -0.08688;4.63638;-3.68904;,
 -3.34212;4.63637;-3.68904;,
 -3.34213;5.85948;3.18896;,
 -0.08688;-13.79202;2.07306;,
 -0.08688;-13.79202;-2.00123;,
 -0.08688;4.63638;-3.68904;,
 -3.34212;4.63637;-3.68904;,
 -3.34212;-10.38201;-3.18740;,
 -3.34212;-10.38201;3.25923;,
 1.52575;-19.38448;-2.88120;,
 1.16269;-23.75347;-2.32645;,
 -1.87300;-23.75347;-2.32645;,
 -2.23610;-19.38449;-2.88120;,
 1.16269;-23.75347;-2.32645;,
 1.16269;-23.75347;2.31201;,
 -1.87300;-23.75347;2.31201;,
 -1.87300;-23.75347;-2.32645;,
 1.16269;-23.75347;2.31201;,
 1.52575;-19.38448;2.86673;,
 -2.23610;-19.38449;2.86673;,
 -1.87300;-23.75347;2.31201;,
 1.52575;-19.38448;2.86673;,
 1.16269;-23.75347;-2.32645;,
 1.52575;-19.38448;-2.88120;,
 -2.23610;-19.38449;-2.88120;,
 -1.87300;-23.75347;-2.32645;,
 -2.23610;-19.38449;2.86673;,
 4.16795;-14.21364;2.92538;,
 4.16795;-15.22187;2.92538;,
 4.16795;-15.22187;-3.25011;,
 4.16795;-14.21364;-3.25011;,
 4.16173;-14.20358;-3.24826;,
 3.54719;-14.91027;-3.24826;,
 -1.67450;-9.48954;-2.68222;,
 -0.96962;-8.78285;-2.68222;,
 4.16173;-15.19790;-3.24826;,
 -0.96960;-20.61863;-2.87785;,
 -1.67450;-19.91195;-2.87785;,
 4.15951;-14.21423;-3.24826;,
 4.16173;-15.19945;2.93904;,
 4.16275;-14.22968;2.93906;,
 -1.67450;-19.99785;2.93904;,
 -0.96960;-20.70452;2.93904;,
 4.16173;-14.20279;2.93904;,
 -0.96960;-8.69772;2.33550;,
 -1.67450;-9.40439;2.33550;,
 3.54716;-14.82514;2.93906;,
 0.80485;-14.78334;1.72915;,
 -3.33869;-10.39052;3.25774;,
 -3.33869;-10.39052;-3.22114;,
 0.80485;-14.78334;-1.69256;,
 -2.52343;-10.89728;-2.64032;,
 -2.10812;-20.97725;-2.64032;,
 -2.10812;-20.97725;0.36656;,
 -2.52343;-10.89728;0.36656;,
 -0.34113;-21.06512;1.55376;,
 0.73675;-12.40268;1.78619;,
 -1.77513;-10.89730;-1.04732;,
 -1.59805;-20.97724;-0.78222;,
 -0.34113;-21.06512;-1.72416;,
 -1.59805;-20.97724;-0.49597;,
 -2.24987;-10.89730;-0.72549;,
 0.73675;-12.40268;-1.71539;,
 6.21098;5.24871;-5.69198;,
 1.06447;-24.15628;-2.38074;,
 -2.72205;-22.42607;-3.67321;,
 -4.62548;1.58477;-3.46367;,
 6.21102;5.24819;-5.63563;,
 -4.62548;1.58435;-3.40725;,
 -2.72206;-22.42652;-3.61681;,
 1.06456;-24.15672;-2.32453;,
 2.80961;-23.57438;-3.23767;,
 2.80961;-23.85775;2.83447;,
 1.23914;-29.64650;2.83447;,
 1.23914;-29.64650;-3.23767;,
 -2.76890;-23.85775;2.83447;,
 -2.76890;-23.57438;-3.23767;,
 -1.16157;-29.64650;-3.23767;,
 -1.16157;-29.64650;2.83447;,
 -1.34656;-35.23413;-5.23247;,
 1.38727;-35.23413;-5.23247;,
 1.22102;-37.67820;-3.40140;,
 -1.18031;-37.67820;-3.40140;,
 1.38727;-35.23413;-5.23247;,
 2.80961;-23.58651;-3.16916;,
 2.79316;-23.67618;-2.83125;,
 1.22102;-37.67820;-3.40140;,
 -2.76890;-23.58651;-3.16916;,
 -1.34656;-35.23413;-5.23247;,
 -1.18031;-37.67820;-3.40140;,
 -2.88036;-23.52674;-2.83125;,
 1.38727;-35.23413;-5.23247;,
 -1.34656;-35.23413;-5.23247;,
 2.79573;-23.80060;2.85199;,
 1.32726;-17.72614;7.67516;,
 1.16831;-36.70364;4.93470;,
 1.16831;-29.64650;2.85199;,
 -1.28656;-17.72614;7.67516;,
 -2.75502;-23.80060;2.85199;,
 -1.12761;-29.64650;2.85199;,
 -1.12761;-36.70364;4.93470;,
 2.79573;-23.80060;2.85199;,
 -2.75502;-23.80060;2.85199;,
 1.34205;-17.62031;7.47382;,
 2.10302;-10.13751;14.98811;,
 1.34205;-28.48229;13.14420;,
 1.34205;-36.66066;4.77946;,
 2.10302;-10.13751;14.98811;,
 -2.03273;-10.13751;14.98811;,
 -1.27178;-28.48229;13.14420;,
 1.34205;-28.48229;13.14420;,
 -2.03273;-10.13751;14.98811;,
 -1.27178;-17.62031;7.47382;,
 -1.27178;-36.66066;4.77946;,
 -1.27178;-28.48229;13.14420;,
 1.34205;-17.62031;7.47382;,
 -1.27178;-17.62031;7.47382;,
 -1.27178;-36.66066;4.77946;,
 1.34205;-36.66066;4.77946;;
 
 42;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;13,12,14,15;,
 4;16,17,18,19;,
 4;16,7,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,34,35,36;,
 4;37,38,39,33;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,45,53,54;,
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
 4;118,115,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;128,125,132,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;142,135,146,147;,
 4;148,149,136,145;;
 
 MeshMaterialList {
  5;
  42;
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
  45;
  0.081849;0.009841;-0.996596;,
  -0.060659;0.010224;-0.998106;,
  -0.201935;0.010399;-0.979344;,
  -0.032634;-0.999467;0.000000;,
  -0.201931;0.010398;0.979345;,
  0.081856;0.009838;0.996596;,
  -0.060654;0.010222;0.998107;,
  0.130292;-0.061294;-0.989579;,
  0.147281;-0.025241;0.988773;,
  0.000000;-0.125963;-0.992035;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.125956;0.992036;,
  1.000000;0.000000;0.000000;,
  -0.055184;0.051412;-0.997152;,
  -0.049177;-0.017584;-0.998635;,
  0.000008;-0.000010;1.000000;,
  -0.056756;0.056345;0.996797;,
  -0.727446;-0.686165;0.000000;,
  -0.999152;-0.041166;0.000000;,
  -0.817334;0.050640;0.573934;,
  -0.526598;0.022534;-0.849816;,
  0.029428;-0.082167;-0.996184;,
  -0.029402;0.082160;0.996185;,
  0.389911;0.920853;0.000000;,
  0.995133;-0.098540;-0.000000;,
  -0.000001;0.984554;-0.175082;,
  -1.000000;-0.000000;-0.000001;,
  0.996565;-0.082814;-0.000000;,
  -0.996564;-0.082823;0.000000;,
  -0.965126;-0.261717;-0.005971;,
  0.966629;-0.256115;-0.005842;,
  0.000000;-0.231702;-0.972787;,
  0.000000;-0.599583;-0.800313;,
  0.992975;-0.116605;-0.020116;,
  -0.978177;-0.107340;-0.177898;,
  -0.954832;-0.122306;0.270810;,
  0.954831;-0.122307;0.270812;,
  -0.999296;-0.017355;-0.033244;,
  0.999296;-0.017355;-0.033245;,
  0.000000;-0.100010;0.994986;,
  0.000000;-0.433543;0.901133;,
  0.000000;0.174429;-0.984670;,
  0.000000;0.621829;-0.783153;,
  0.000000;0.708590;-0.705621;,
  0.000000;-0.715027;0.699096;;
  42;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;3,3,3,3;,
  4;5,5,6,6;,
  4;6,6,4,4;,
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
  4;31,31,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;41,41,31,31;,
  4;36,36,36,36;,
  4;35,35,35,35;,
  4;42,42,42,42;,
  4;38,38,38,38;,
  4;39,39,40,40;,
  4;37,37,37,37;,
  4;43,43,43,43;,
  4;44,44,40,40;;
 }
 MeshTextureCoords {
  150;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
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