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
 104;
 -1.02728;-0.90348;-2.91074;,
 -0.58465;-0.59837;-2.92953;,
 -0.58465;-1.32184;-4.07720;,
 -1.20869;-1.40898;-3.24213;,
 0.35282;-0.59837;-2.92953;,
 0.35282;-1.32184;-4.07720;,
 0.95177;-0.87978;-2.93769;,
 1.13826;-1.40898;-3.26910;,
 -0.58465;-1.94137;-6.02859;,
 -1.20869;-1.94137;-4.27725;,
 0.35282;-1.94137;-6.02859;,
 1.13826;-1.94137;-4.30422;,
 -0.58465;-2.47156;-6.01184;,
 -1.20869;-2.47156;-4.26052;,
 0.35282;-2.47156;-6.01184;,
 1.13826;-2.47156;-4.28747;,
 0.95177;-0.87978;-2.93769;,
 1.05269;-0.60164;-2.02648;,
 1.29027;-1.04341;-2.02648;,
 1.13826;-1.40898;-3.26910;,
 1.10866;-0.24742;-1.03318;,
 1.32578;-0.92067;-1.03318;,
 0.96321;-0.24742;0.19985;,
 1.13691;-0.92067;0.34985;,
 1.29027;-1.94100;-2.02648;,
 1.13826;-1.94137;-4.30422;,
 1.32578;-1.94100;-1.03318;,
 1.13691;-1.94100;0.34985;,
 1.29027;-2.35887;-2.02985;,
 1.13826;-2.47156;-4.28747;,
 1.32578;-2.35887;-1.03318;,
 1.13691;-2.47156;0.34985;,
 0.96321;-0.24742;0.19985;,
 0.35282;-0.14522;0.94919;,
 0.35282;-0.92067;1.08640;,
 1.13691;-0.92067;0.34985;,
 -0.58465;-0.14522;0.94919;,
 -0.58465;-0.92067;1.08640;,
 -1.06233;-0.23462;0.33170;,
 -1.21550;-0.92067;0.48170;,
 0.35282;-1.94100;1.08640;,
 1.13691;-1.94100;0.34985;,
 -0.58465;-1.94100;1.08640;,
 -1.12049;-1.94100;0.48170;,
 0.35282;-2.47156;1.08640;,
 1.13691;-2.47156;0.34985;,
 -0.58465;-2.47156;1.08640;,
 -1.12049;-2.47156;0.48170;,
 -1.06233;-0.23462;0.33170;,
 -1.33859;-0.36235;-1.03318;,
 -1.47269;-0.92067;-1.03318;,
 -1.21550;-0.92067;0.48170;,
 -1.25576;-0.66538;-2.02648;,
 -1.43717;-1.04341;-2.02648;,
 -1.02728;-0.90348;-2.91074;,
 -1.20869;-1.40898;-3.24213;,
 -1.38897;-1.94100;-1.03318;,
 -1.12049;-1.94100;0.48170;,
 -1.35347;-1.94100;-2.02648;,
 -1.20869;-1.94137;-4.27725;,
 -1.38897;-2.35887;-1.03318;,
 -1.12049;-2.47156;0.48170;,
 -1.35347;-2.35887;-2.02985;,
 -1.20869;-2.47156;-4.26052;,
 -0.58465;-0.14522;0.94919;,
 -0.59648;-0.14522;-1.03318;,
 -1.33859;-0.36235;-1.03318;,
 0.35282;-0.14522;0.94919;,
 0.36465;-0.14522;-1.03318;,
 1.10866;-0.24742;-1.03318;,
 -0.58465;-0.27009;-2.02648;,
 -1.25576;-0.66538;-2.02648;,
 0.35282;-0.27009;-2.02648;,
 1.05269;-0.60164;-2.02648;,
 -0.58465;-0.59837;-2.92953;,
 -1.02728;-0.90348;-2.91074;,
 0.35282;-0.59837;-2.92953;,
 0.95177;-0.87978;-2.93769;,
 -1.38897;-2.35887;-1.03318;,
 -0.59648;-2.35887;-1.03318;,
 -0.58465;-2.47156;1.08640;,
 0.36465;-2.35887;-1.03318;,
 0.35282;-2.47156;1.08640;,
 1.32578;-2.35887;-1.03318;,
 -1.35347;-2.35887;-2.02985;,
 -0.58465;-2.35887;-2.02985;,
 0.35282;-2.35887;-2.02985;,
 1.29027;-2.35887;-2.02985;,
 -1.20869;-2.47156;-4.26052;,
 -0.58465;-2.47156;-6.01184;,
 0.35282;-2.47156;-6.01184;,
 1.13826;-2.47156;-4.28747;,
 0.01286;0.70807;-0.28854;,
 -0.69947;-0.00426;-0.28854;,
 0.01286;-0.00426;0.42378;,
 0.01286;0.70807;-0.28854;,
 0.72519;-0.00426;-0.28854;,
 0.01286;0.70807;-0.28854;,
 0.01286;-0.00426;-1.00087;,
 0.01286;-0.00426;-1.00087;,
 0.01286;-0.71658;-0.28854;,
 0.01286;-0.71658;-0.28854;,
 0.01286;-0.71658;-0.28854;,
 0.01286;-0.71658;-0.28854;;
 
 63;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;19,18,24,25;,
 4;18,21,26,24;,
 4;21,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;35,34,40,41;,
 4;34,37,42,40;,
 4;37,39,43,42;,
 4;41,40,44,45;,
 4;40,42,46,44;,
 4;42,43,47,46;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;51,50,56,57;,
 4;50,53,58,56;,
 4;53,55,59,58;,
 4;57,56,60,61;,
 4;56,58,62,60;,
 4;58,59,63,62;,
 4;48,64,65,66;,
 4;64,67,68,65;,
 4;67,22,69,68;,
 4;66,65,70,71;,
 4;65,68,72,70;,
 4;68,69,73,72;,
 4;71,70,74,75;,
 4;70,72,76,74;,
 4;72,73,77,76;,
 4;78,79,80,61;,
 4;79,81,82,80;,
 4;81,83,31,82;,
 4;84,85,79,78;,
 4;85,86,81,79;,
 4;86,87,83,81;,
 4;88,89,85,84;,
 4;89,90,86,85;,
 4;90,91,87,86;,
 3;92,93,94;,
 3;95,94,96;,
 3;97,96,98;,
 3;99,100,93;,
 3;93,101,94;,
 3;94,102,96;,
 3;96,103,98;,
 3;92,99,93;,
 3;98,95,93;;
 
 MeshMaterialList {
  7;
  63;
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
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.561600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.276000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.125600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  81;
  -0.667729;0.642976;-0.375125;,
  -0.296340;0.849066;-0.437345;,
  0.234782;0.864368;-0.444687;,
  -0.814018;0.487140;-0.316336;,
  -0.328409;0.843103;-0.425822;,
  0.268636;0.855635;-0.442407;,
  -0.956048;0.195806;-0.218250;,
  -0.329531;0.888435;-0.319518;,
  0.273464;0.904630;-0.326898;,
  -0.979373;-0.005735;-0.201979;,
  -0.941933;-0.010597;-0.335633;,
  0.000000;-0.031577;-0.999501;,
  0.612886;0.696042;-0.374026;,
  0.659643;0.711157;-0.243160;,
  0.795018;0.600244;-0.087481;,
  0.778853;0.538933;-0.320842;,
  0.964236;0.233101;-0.126149;,
  0.984526;0.173566;0.024163;,
  0.941264;0.229712;-0.247498;,
  0.998184;0.015943;-0.058089;,
  0.998750;0.000036;0.049989;,
  0.969592;-0.007057;-0.244625;,
  0.998686;-0.000324;-0.051255;,
  0.998749;0.000072;0.050004;,
  0.873947;0.270061;0.404084;,
  0.394241;0.218693;0.892607;,
  -0.403315;0.211711;0.890234;,
  0.889797;0.137356;0.435195;,
  0.383530;0.109279;0.917040;,
  -0.400106;0.097356;0.911283;,
  0.888749;0.000000;0.458394;,
  0.368200;0.000000;0.929746;,
  -0.400957;-0.008788;0.916055;,
  0.888749;0.000000;0.458394;,
  -0.410361;0.000000;0.911923;,
  -0.877228;0.234126;0.419114;,
  -0.838685;0.541371;-0.059366;,
  -0.708765;0.657079;-0.256708;,
  -0.893652;0.087845;0.440080;,
  -0.993559;0.102486;0.048352;,
  -0.971576;0.183996;-0.148946;,
  -0.895750;-0.030812;0.443489;,
  -0.996589;-0.043547;0.070094;,
  -0.998004;-0.017944;-0.060551;,
  -0.900338;0.000000;0.435192;,
  -0.997560;0.000072;0.069815;,
  -0.998747;-0.000309;-0.050048;,
  -0.157756;0.983438;-0.089230;,
  0.107647;0.990323;-0.087593;,
  -0.232829;0.937558;-0.258409;,
  0.173059;0.950849;-0.256783;,
  0.007531;-0.999544;-0.029235;,
  -0.006265;-0.999527;-0.030110;,
  0.009904;-0.999808;0.016917;,
  -0.007754;-0.999828;0.016842;,
  0.909963;-0.013094;-0.414483;,
  -0.233315;0.972270;-0.015949;,
  -0.117475;0.993043;-0.008031;,
  0.075827;0.997112;0.004274;,
  0.151216;0.988464;0.008523;,
  0.015063;-0.999377;-0.031914;,
  0.015055;-0.998177;-0.058448;,
  0.030107;-0.997509;-0.063789;,
  -0.012524;-0.998108;-0.060194;,
  -0.012531;-0.999355;-0.033664;,
  -0.025046;-0.997419;-0.067285;,
  0.019810;-0.999610;0.019688;,
  -0.015510;-0.999689;0.019538;,
  0.039604;-0.998440;0.039360;,
  0.019806;-0.999231;0.033832;,
  -0.015507;-0.999312;0.033681;,
  -0.031010;-0.998755;0.039065;,
  -0.577348;0.577348;0.577356;,
  0.577350;0.577350;-0.577350;,
  0.577347;0.577348;0.577356;,
  -0.577348;-0.577356;-0.577348;,
  -0.577345;-0.577353;0.577353;,
  0.577345;-0.577353;0.577353;,
  0.577348;-0.577356;-0.577348;,
  -0.577350;0.577350;-0.577350;,
  0.577350;-0.577350;0.577350;;
  63;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,12,15,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,15,18,8;,
  4;6,10,10,9;,
  4;11,11,11,11;,
  4;55,18,21,55;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;14,24,27,17;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;17,27,30,20;,
  4;18,19,22,21;,
  4;19,20,23,22;,
  4;20,30,33,23;,
  4;24,25,28,27;,
  4;25,26,29,28;,
  4;26,35,38,29;,
  4;27,28,31,30;,
  4;28,29,32,31;,
  4;29,38,41,32;,
  4;30,31,31,33;,
  4;31,32,34,31;,
  4;32,41,44,34;,
  4;35,36,39,38;,
  4;36,37,40,39;,
  4;37,0,3,40;,
  4;38,39,42,41;,
  4;39,40,43,42;,
  4;40,3,6,43;,
  4;41,42,45,44;,
  4;42,43,46,45;,
  4;43,6,9,46;,
  4;56,57,47,56;,
  4;57,58,48,47;,
  4;58,59,59,48;,
  4;36,47,49,37;,
  4;47,48,50,49;,
  4;48,14,13,50;,
  4;37,49,1,0;,
  4;49,50,2,1;,
  4;50,13,12,2;,
  4;60,51,61,62;,
  4;51,52,63,61;,
  4;52,64,65,63;,
  4;66,53,51,60;,
  4;53,54,52,51;,
  4;54,67,64,52;,
  4;68,69,53,66;,
  4;69,70,54,53;,
  4;70,71,67,54;,
  3;72,72,72;,
  3;74,74,74;,
  3;73,73,73;,
  3;75,75,75;,
  3;76,76,76;,
  3;77,77,77;,
  3;78,78,78;,
  3;79,79,79;,
  3;80,80,80;;
 }
 MeshTextureCoords {
  104;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.375000;0.000000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}
