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
 42;
 -1.04990;0.23702;22.71023;,
 0.36922;0.23702;22.71023;,
 0.36922;0.23702;4.75954;,
 -1.04990;0.23703;4.75954;,
 -1.04991;-0.03519;28.22408;,
 0.96615;-0.03517;22.71024;,
 0.36922;0.23702;22.71023;,
 -1.04990;0.23702;22.71023;,
 -1.04990;-0.30736;22.71026;,
 0.36921;-0.30737;22.71026;,
 -1.04990;-0.30736;4.75952;,
 0.36921;-0.30737;4.75952;,
 0.36921;-0.30737;22.71026;,
 -1.04990;-0.30736;22.71026;,
 -1.04991;-0.03519;28.22408;,
 -1.04991;-0.03519;4.75954;,
 -1.04990;0.23702;22.71023;,
 -1.04990;0.23703;4.75954;,
 0.96615;-0.03517;22.71024;,
 0.96615;-0.03519;4.75954;,
 0.36922;0.23702;22.71023;,
 0.36922;0.23702;4.75954;,
 -1.45976;0.55482;5.04094;,
 1.25024;0.55482;5.04094;,
 1.25024;0.55483;-4.43363;,
 -1.45976;0.55483;-4.43363;,
 -1.45977;-0.62516;5.04097;,
 1.25023;-0.62517;5.04097;,
 1.25024;0.55482;5.04094;,
 -1.45976;0.55482;5.04094;,
 -1.45978;-0.62516;-4.43367;,
 1.25023;-0.62515;-4.43367;,
 1.25023;-0.62517;5.04097;,
 -1.45977;-0.62516;5.04097;,
 -1.45976;0.55483;-4.43363;,
 1.25024;0.55483;-4.43363;,
 1.25023;-0.62515;-4.43367;,
 -1.45978;-0.62516;-4.43367;,
 -1.45976;0.55482;5.04094;,
 -1.45976;0.55483;-4.43363;,
 1.25024;0.55482;5.04094;,
 1.25024;0.55483;-4.43363;;
 
 28;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,6;,
 3;4,6,7;,
 3;4,8,9;,
 3;4,9,5;,
 3;10,11,12;,
 3;10,12,13;,
 3;8,14,15;,
 3;8,15,10;,
 3;14,16,17;,
 3;14,17,15;,
 3;18,9,11;,
 3;18,11,19;,
 3;20,18,19;,
 3;20,19,21;,
 3;22,23,24;,
 3;22,24,25;,
 3;26,27,28;,
 3;26,28,29;,
 3;30,31,32;,
 3;30,32,33;,
 3;34,35,36;,
 3;34,36,37;,
 3;26,38,39;,
 3;26,39,37;,
 3;40,27,36;,
 3;40,36,41;;
 
 MeshMaterialList {
  1;
  28;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  38;
  0.000004;1.000000;0.000001;,
  0.141161;0.989987;0.000000;,
  0.000000;0.999865;0.016441;,
  0.210101;0.972336;0.102078;,
  0.253973;0.966350;0.040819;,
  0.413716;0.907294;0.075206;,
  -0.000009;-0.999696;0.024658;,
  -0.000008;-1.000000;-0.000000;,
  0.168982;-0.984774;0.040815;,
  0.282297;-0.959327;0.000000;,
  -1.000000;-0.000015;0.000000;,
  0.414870;-0.909881;0.000001;,
  0.000002;1.000000;0.000002;,
  -0.000001;1.000000;0.000001;,
  -0.000003;1.000000;0.000000;,
  -0.000000;0.000021;1.000000;,
  0.000000;0.000021;1.000000;,
  0.000001;-1.000000;-0.000001;,
  0.000003;-1.000000;-0.000002;,
  0.210100;-0.972337;0.102073;,
  0.414364;-0.908730;0.050121;,
  -1.000000;-0.000043;-0.000000;,
  -1.000000;0.000015;0.000000;,
  -1.000000;-0.000048;-0.000000;,
  -1.000000;0.000045;0.000000;,
  -1.000000;0.000042;0.000000;,
  0.414902;0.909866;-0.000000;,
  -0.000000;0.000021;1.000000;,
  -0.000002;-1.000000;-0.000000;,
  -0.000000;0.000031;-1.000000;,
  0.000000;0.000031;-1.000000;,
  -0.000000;0.000031;-1.000000;,
  -1.000000;0.000010;0.000000;,
  -1.000000;0.000008;-0.000000;,
  -1.000000;0.000013;0.000000;,
  1.000000;-0.000010;-0.000000;,
  1.000000;-0.000013;0.000000;,
  1.000000;-0.000008;-0.000000;;
  28;
  3;2,4,1;,
  3;2,1,0;,
  3;3,5,4;,
  3;3,4,2;,
  3;19,6,8;,
  3;19,8,20;,
  3;7,9,8;,
  3;7,8,6;,
  3;21,22,10;,
  3;21,10,23;,
  3;22,24,25;,
  3;22,25,10;,
  3;20,8,9;,
  3;20,9,11;,
  3;4,5,26;,
  3;4,26,1;,
  3;13,14,13;,
  3;13,13,12;,
  3;15,16,15;,
  3;15,15,27;,
  3;17,18,17;,
  3;17,17,28;,
  3;29,30,29;,
  3;29,29,31;,
  3;32,33,32;,
  3;32,32,34;,
  3;35,36,35;,
  3;35,35,37;;
 }
 MeshTextureCoords {
  42;
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;;
 }
}
