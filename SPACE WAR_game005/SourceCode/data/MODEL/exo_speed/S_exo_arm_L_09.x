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
 5.05944;1.84069;-2.33952;,
 5.05944;-1.95886;-2.33952;,
 1.25989;-1.95886;-2.33952;,
 1.25989;1.84069;-2.33952;,
 5.05944;-1.95886;-2.33952;,
 5.70942;-2.60886;-0.09987;,
 0.60991;-2.60886;-0.09987;,
 1.25989;-1.95886;-2.33952;,
 5.05944;-1.95886;2.13982;,
 1.25989;-1.95886;2.13982;,
 5.05944;-1.95886;2.13982;,
 5.05944;1.84069;2.13982;,
 1.25989;1.84069;2.13982;,
 1.25989;-1.95886;2.13982;,
 5.05944;1.84069;2.13982;,
 5.70942;2.49067;-0.09987;,
 0.60991;2.49067;-0.09987;,
 1.25989;1.84069;2.13982;,
 5.05944;1.84069;-2.33952;,
 1.25989;1.84069;-2.33952;,
 5.70942;-2.60886;-0.09987;,
 5.70942;2.49067;-0.09987;,
 5.05944;-1.95886;-2.33952;,
 5.05944;1.84069;-2.33952;,
 0.60991;2.49067;-0.09987;,
 0.60991;-2.60886;-0.09987;,
 1.25989;1.84069;-2.33952;,
 1.25989;-1.95886;-2.33952;,
 6.54568;-2.18472;-4.72830;,
 6.54567;1.39794;-4.72830;,
 9.66593;1.13804;-6.19489;,
 9.66593;-1.38197;-6.19489;,
 9.66705;-1.40208;-6.20313;,
 9.62552;1.13346;-6.20313;,
 16.95461;1.84584;-3.53222;,
 16.95461;-0.24713;-3.53222;,
 24.02312;1.41472;-3.43208;,
 24.02311;-0.24968;-3.43208;,
 6.54567;1.39794;-4.72830;,
 7.14692;2.40701;4.03779;,
 9.49949;2.79664;3.03244;,
 9.66593;1.13804;-6.19489;,
 9.62552;1.13346;-6.20313;,
 9.47511;2.78640;3.08066;,
 20.41416;1.84584;-0.12981;,
 16.95461;1.84584;-3.53222;,
 24.48619;1.41472;-1.49224;,
 24.02312;1.41472;-3.43208;,
 7.14692;2.40701;4.03779;,
 7.14694;-2.98951;4.03779;,
 9.49950;-2.03318;3.03244;,
 9.49949;2.79664;3.03244;,
 9.47511;2.78640;3.08066;,
 9.51662;-2.03318;3.08066;,
 20.41416;-0.24714;-0.12981;,
 20.41416;1.84584;-0.12981;,
 24.48621;-0.24969;-1.49224;,
 24.48619;1.41472;-1.49224;,
 7.14694;-2.98951;4.03779;,
 6.54568;-2.18472;-4.72830;,
 9.66593;-1.38197;-6.19489;,
 9.49950;-2.03318;3.03244;,
 9.51662;-2.03318;3.08066;,
 9.66705;-1.40208;-6.20313;,
 16.95461;-0.24713;-3.53222;,
 20.41416;-0.24714;-0.12981;,
 6.54567;1.39794;-4.72830;,
 6.54568;-2.18472;-4.72830;,
 7.74128;2.14219;-0.59391;,
 15.94528;1.85295;-3.01726;,
 9.63104;1.38930;-5.27234;,
 7.50234;1.54085;-4.27123;,
 9.82241;2.53880;1.21036;,
 18.78240;1.82381;-1.77392;,
 16.50588;1.66413;-2.68723;,
 8.07471;2.25688;-0.11858;,
 9.70531;-1.99788;3.03125;,
 9.70531;2.85410;3.03125;,
 7.90719;2.53633;3.71388;,
 7.90719;-2.74939;3.71388;,
 9.70531;2.81170;2.10807;,
 7.90719;2.25267;0.76123;,
 9.60753;2.49424;1.02502;,
 18.37314;1.86656;-1.88097;,
 17.95928;1.86655;-2.09467;,
 9.33956;2.49425;0.82561;,
 8.90584;-2.35097;3.34170;,
 8.90586;2.73060;3.34170;,
 8.59514;2.66333;3.45769;,
 8.59513;-2.49710;3.45769;,
 8.95033;2.57787;1.51897;,
 8.74178;2.51393;1.39790;,
 5.84848;-1.40239;-1.29264;,
 5.84848;1.22429;-1.29264;,
 7.27074;1.46706;-1.53537;,
 7.27074;-1.64512;-1.53537;,
 5.84848;1.22429;-1.29264;,
 5.84848;1.22429;1.33404;,
 7.27074;1.46706;1.57674;,
 7.27074;1.46706;-1.53537;,
 5.84848;1.22429;1.33404;,
 5.84848;-1.40239;1.33404;,
 7.27074;-1.64512;1.57674;,
 7.27074;1.46706;1.57674;;
 
 32;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;15,18,19,16;,
 4;14,8,20,21;,
 4;21,20,22,23;,
 4;24,25,9,17;,
 4;26,27,25,24;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;45,44,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;55,54,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;58,39,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;77,80,81,78;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;87,90,91,88;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;;
 
 MeshMaterialList {
  5;
  32;
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
  2,
  2,
  2,
  2,
  1,
  1,
  1,
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
  39;
  0.000000;0.000000;-1.000000;,
  -0.000001;-1.000000;-0.000002;,
  -0.000001;-0.960373;0.278720;,
  0.000000;0.000000;1.000000;,
  0.000001;1.000000;-0.000002;,
  -0.000001;-0.960371;-0.278724;,
  0.000001;0.960375;0.278710;,
  0.000001;0.960374;-0.278714;,
  0.960375;0.000000;0.278711;,
  1.000000;0.000000;-0.000002;,
  0.960374;0.000000;-0.278716;,
  -1.000000;0.000000;-0.000002;,
  -0.960375;0.000000;0.278711;,
  -0.960374;0.000000;-0.278716;,
  -0.425378;-0.000000;-0.905016;,
  0.342864;0.002812;-0.939381;,
  0.181061;0.001426;-0.983471;,
  0.014166;-0.000000;-0.999900;,
  -0.102852;0.985024;-0.138382;,
  0.017205;0.992419;-0.121694;,
  0.048476;0.995415;-0.082451;,
  0.079624;0.995897;-0.042999;,
  0.392964;0.000001;0.919554;,
  0.281920;0.001216;0.959437;,
  0.299658;0.000609;0.954046;,
  0.317293;0.000003;0.948327;,
  -0.009613;0.986635;-0.162659;,
  0.007751;0.978460;-0.206289;,
  0.354921;0.000000;0.934896;,
  -0.211006;0.975041;-0.069073;,
  0.046643;0.996051;-0.075539;,
  0.349724;-0.000001;0.936853;,
  -0.243452;0.965987;-0.087184;,
  -0.168233;0.000000;-0.985747;,
  -0.168259;0.985743;0.000000;,
  -0.168213;0.000000;0.985751;,
  0.277596;-0.956753;-0.086974;,
  0.151689;-0.983842;-0.095107;,
  -0.997656;-0.000002;0.068428;;
  32;
  4;0,0,0,0;,
  4;5,1,1,5;,
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;6,4,4,6;,
  4;4,7,7,4;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;11,11,12,12;,
  4;13,13,11,11;,
  4;14,14,14,14;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;18,18,18,18;,
  4;19,19,20,20;,
  4;20,20,21,21;,
  4;22,22,22,22;,
  4;23,23,24,24;,
  4;24,24,25,25;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;;
 }
 MeshTextureCoords {
  104;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  0.000000;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  0.000000;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  0.000000;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  0.000000;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
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
  0.333330;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.333330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.333330;1.000000;,
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
  0.000000;1.000000;;
 }
}