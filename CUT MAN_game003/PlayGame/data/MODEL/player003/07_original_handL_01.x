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
 60;
 -0.08746;1.17437;-0.81501;,
 1.53921;1.17436;-0.81501;,
 1.53921;-0.55341;-1.53369;,
 -0.08746;-0.55341;-1.53369;,
 1.53921;-1.36346;-1.05005;,
 -0.08747;-1.36346;-1.05005;,
 3.16586;1.17437;-0.81501;,
 3.16587;-0.55340;-1.53369;,
 3.16586;-1.36347;-1.05005;,
 4.79254;0.58587;-0.81501;,
 4.38346;-0.55341;-1.53369;,
 3.69230;-1.36208;-1.05005;,
 -0.08747;-1.36346;-1.05005;,
 1.53921;-1.36346;-1.05005;,
 1.53921;-1.47011;0.47631;,
 -0.08747;-1.47010;0.47631;,
 1.53921;-1.45097;1.95638;,
 -0.08746;-1.45097;1.95638;,
 3.16586;-1.36347;-1.05005;,
 3.16587;-1.47009;0.47631;,
 3.16587;-1.45097;1.95638;,
 3.69230;-1.36208;-1.05005;,
 3.69229;-1.46870;0.47631;,
 3.69229;-1.44959;1.95638;,
 -0.08746;-1.45097;1.95638;,
 1.53921;-1.45097;1.95638;,
 1.53921;-0.55341;2.48631;,
 -0.08746;-0.55341;2.48631;,
 1.53920;0.71157;2.03532;,
 -0.08746;0.71158;2.03532;,
 3.16587;-1.45097;1.95638;,
 3.16587;-0.55340;2.48631;,
 3.16588;0.71157;2.03532;,
 3.69229;-1.44959;1.95638;,
 4.38347;-1.14191;2.48631;,
 4.79253;0.12308;2.03532;,
 -0.08746;0.71158;2.03532;,
 1.53920;0.71157;2.03532;,
 1.53921;1.45159;0.47631;,
 -0.08746;1.45160;0.47631;,
 1.53921;1.17436;-0.81501;,
 -0.08746;1.17437;-0.81501;,
 3.16588;0.71157;2.03532;,
 3.16587;1.45161;0.47631;,
 3.16586;1.17437;-0.81501;,
 4.79253;0.12308;2.03532;,
 4.79253;0.86310;0.47631;,
 4.79254;0.58587;-0.81501;,
 -0.08746;1.45160;0.47631;,
 -0.08746;-0.55341;0.47631;,
 -0.08747;-1.47010;0.47631;,
 -0.08746;1.17437;-0.81501;,
 -0.08746;-0.55341;-1.53369;,
 -0.08747;-1.36346;-1.05005;,
 4.79253;0.86310;0.47631;,
 4.50097;-0.55341;0.47631;,
 3.69229;-1.46870;0.47631;,
 4.79254;0.58587;-0.81501;,
 4.38346;-0.55341;-1.53369;,
 3.69230;-1.36208;-1.05005;;
 
 32;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;1,6,7,2;,
 4;2,7,8,4;,
 4;6,9,10,7;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;13,18,19,14;,
 4;14,19,20,16;,
 4;18,21,22,19;,
 4;19,22,23,20;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;25,30,31,26;,
 4;26,31,32,28;,
 4;30,33,34,31;,
 4;31,34,35,32;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;37,42,43,38;,
 4;38,43,44,40;,
 4;42,45,46,43;,
 4;43,46,47,44;,
 4;36,48,49,27;,
 4;27,49,50,17;,
 4;48,51,52,49;,
 4;49,52,53,50;,
 4;54,45,34,55;,
 4;55,34,23,56;,
 4;57,54,55,58;,
 4;58,55,56,59;;
 
 MeshMaterialList {
  1;
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
 }
 MeshNormals {
  47;
  0.000004;0.768665;-0.639651;,
  0.000001;-0.071971;-0.997407;,
  -0.000001;0.768665;-0.639652;,
  -0.000000;-0.071969;-0.997407;,
  0.118889;0.767943;-0.629388;,
  0.024827;-0.058437;-0.997982;,
  0.234720;0.756485;-0.610440;,
  0.050027;-0.044647;-0.997749;,
  -0.000002;-0.851923;-0.523668;,
  -0.000002;-0.999596;-0.028411;,
  -0.000000;-0.851923;-0.523668;,
  0.000001;-0.999596;-0.028410;,
  0.000932;-0.851972;-0.523587;,
  0.001316;-0.999596;-0.028409;,
  0.300723;-0.870449;-0.389724;,
  0.379082;-0.923715;-0.055208;,
  -0.000001;-0.865228;0.501378;,
  0.000001;-0.095293;0.995449;,
  0.000002;-0.865228;0.501378;,
  0.000001;-0.095291;0.995449;,
  -0.041500;-0.874693;0.482897;,
  -0.004938;-0.119136;0.992866;,
  0.202538;-0.935173;0.290569;,
  -0.009990;-0.143469;0.989604;,
  0.000003;0.670619;0.741802;,
  0.000006;0.993297;0.115591;,
  0.000001;0.670618;0.741803;,
  -0.000001;0.993297;0.115592;,
  0.120608;0.658518;0.742838;,
  0.172115;0.978396;0.114531;,
  0.239958;0.636626;0.732890;,
  0.338136;0.934636;0.110087;,
  -1.000000;0.000001;0.000000;,
  0.863257;-0.501514;-0.057203;,
  -1.000000;-0.000003;-0.000001;,
  -1.000000;-0.000002;-0.000002;,
  -1.000000;-0.000001;0.000002;,
  -1.000000;0.000004;0.000002;,
  -1.000000;0.000001;0.000004;,
  -1.000000;-0.000000;-0.000002;,
  -1.000000;0.000003;-0.000001;,
  -1.000000;0.000007;-0.000000;,
  0.965511;-0.257781;-0.036565;,
  0.963061;-0.260832;-0.066925;,
  0.842808;-0.530881;-0.088547;,
  0.967056;-0.254488;-0.006171;,
  0.881454;-0.471539;-0.026265;;
  32;
  4;0,2,3,1;,
  4;1,3,10,8;,
  4;2,4,5,3;,
  4;3,5,12,10;,
  4;4,6,7,5;,
  4;5,7,14,12;,
  4;8,10,11,9;,
  4;9,11,18,16;,
  4;10,12,13,11;,
  4;11,13,20,18;,
  4;12,14,15,13;,
  4;13,15,22,20;,
  4;16,18,19,17;,
  4;17,19,26,24;,
  4;18,20,21,19;,
  4;19,21,28,26;,
  4;20,22,23,21;,
  4;21,23,30,28;,
  4;24,26,27,25;,
  4;25,27,2,0;,
  4;26,28,29,27;,
  4;27,29,4,2;,
  4;28,30,31,29;,
  4;29,31,6,4;,
  4;34,35,32,36;,
  4;36,32,37,38;,
  4;35,39,40,32;,
  4;32,40,41,37;,
  4;42,43,44,33;,
  4;33,44,22,15;,
  4;45,42,33,46;,
  4;46,33,15,14;;
 }
 MeshTextureCoords {
  60;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
