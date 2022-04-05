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
 38;
 0.09473;-1.04098;-0.10613;,
 1.72143;-1.04097;-0.10612;,
 1.72141;1.23046;-1.22864;,
 0.09474;1.23045;-1.22865;,
 4.02267;-0.83828;0.01479;,
 3.34804;1.23046;-1.22864;,
 4.02267;-0.83828;0.01479;,
 4.97475;0.64196;-1.22864;,
 0.09474;-1.09429;-1.87430;,
 1.72143;-1.55262;-1.87430;,
 1.72143;-1.04097;-0.10612;,
 0.09473;-1.04098;-0.10613;,
 0.09474;-1.08470;-3.61935;,
 1.72142;-1.08471;-3.61934;,
 4.14723;-1.09391;-1.87430;,
 4.02267;-0.83828;0.01479;,
 4.49872;-0.55692;-3.59257;,
 0.09474;0.62904;-3.43332;,
 2.53475;0.62905;-3.43331;,
 1.72142;-1.08471;-3.61934;,
 0.09474;-1.08470;-3.61935;,
 4.49872;-0.55692;-3.59257;,
 0.09474;1.23045;-1.22865;,
 1.72141;1.23046;-1.22864;,
 2.53475;0.62905;-3.43331;,
 0.09474;0.62904;-3.43332;,
 3.34804;1.23046;-1.22864;,
 2.53475;0.62905;-3.43331;,
 4.97475;0.64196;-1.22864;,
 4.49872;-0.55692;-3.59257;,
 0.09474;-1.09429;-1.87430;,
 0.09474;1.23045;-1.22865;,
 0.09473;-1.04098;-0.10613;,
 0.09474;1.23045;-1.22865;,
 4.14723;-1.09391;-1.87430;,
 4.97475;0.64196;-1.22864;,
 4.97475;0.64196;-1.22864;,
 4.02267;-0.83828;0.01479;;
 
 26;
 3;0,1,2;,
 3;0,2,3;,
 3;1,4,5;,
 3;1,5,2;,
 3;5,6,7;,
 3;8,9,10;,
 3;8,10,11;,
 3;12,13,9;,
 3;12,9,8;,
 3;9,14,15;,
 3;9,15,10;,
 3;13,16,14;,
 3;13,14,9;,
 3;17,18,19;,
 3;17,19,20;,
 3;18,21,19;,
 3;22,23,24;,
 3;22,24,25;,
 3;23,26,27;,
 3;26,28,29;,
 3;26,29,27;,
 3;20,30,31;,
 3;20,31,25;,
 3;30,32,33;,
 3;34,29,35;,
 3;36,37,34;;
 
 MeshMaterialList {
  1;
  26;
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
   0.800000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  33;
  -0.000003;0.443042;0.896501;,
  -0.000003;0.443043;0.896500;,
  0.056037;0.527715;0.847571;,
  -0.000005;0.443043;0.896500;,
  -0.180335;-0.978581;0.099290;,
  -0.029646;0.459831;0.887512;,
  -0.017261;-0.999411;0.029661;,
  0.522671;-0.851283;-0.046179;,
  -0.138000;-0.981260;-0.134477;,
  0.121247;-0.958359;-0.258548;,
  0.000003;0.107918;-0.994160;,
  -0.005998;0.110731;-0.993832;,
  0.037269;0.499985;0.865232;,
  0.607844;-0.784795;-0.120923;,
  0.199626;0.551797;0.809734;,
  -0.064929;-0.978595;0.195287;,
  0.000005;-0.999546;0.030137;,
  0.418686;-0.885749;0.200378;,
  -0.003998;0.109794;-0.993946;,
  0.000003;0.107918;-0.994160;,
  0.279044;0.656701;-0.700627;,
  -0.000004;0.964748;-0.263174;,
  -0.000003;0.964748;-0.263175;,
  0.116123;0.946515;-0.301038;,
  -0.000003;0.964749;-0.263173;,
  0.257050;0.886148;-0.385573;,
  0.298662;0.825547;-0.478824;,
  -1.000000;0.000001;-0.000002;,
  -1.000000;-0.000002;-0.000001;,
  -1.000000;-0.000000;-0.000002;,
  -1.000000;0.000004;-0.000005;,
  -1.000000;-0.000002;-0.000004;,
  0.887298;-0.453731;0.082649;;
  26;
  3;3,5,1;,
  3;3,1,0;,
  3;5,2,12;,
  3;5,12,1;,
  3;12,2,14;,
  3;4,6,15;,
  3;4,15,16;,
  3;8,9,6;,
  3;8,6,4;,
  3;6,7,17;,
  3;6,17,15;,
  3;9,13,7;,
  3;9,7,6;,
  3;10,11,18;,
  3;10,18,19;,
  3;11,20,18;,
  3;21,22,23;,
  3;21,23,24;,
  3;22,25,23;,
  3;25,26,20;,
  3;25,20,23;,
  3;27,28,29;,
  3;27,29,30;,
  3;28,31,29;,
  3;7,13,32;,
  3;32,17,7;;
 }
 MeshTextureCoords {
  38;
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.000000;0.333330;,
  0.000000;0.000000;,
  0.500000;0.666670;,
  0.000000;0.666670;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.000000;0.333330;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.500000;0.666670;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.666670;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.000000;0.333330;,
  0.000000;0.000000;,
  0.500000;0.666670;,
  0.000000;0.666670;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;;
 }
}
