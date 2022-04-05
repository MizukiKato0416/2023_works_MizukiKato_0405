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
 62;
 -0.00000;16.74957;-0.06454;,
 3.39964;15.58446;-2.77566;,
 -0.00000;15.58446;-4.41284;,
 -0.00000;16.74957;-0.06454;,
 4.23928;15.58446;0.90305;,
 -0.00000;16.74957;-0.06454;,
 1.88666;15.58446;3.85315;,
 -0.00000;16.74957;-0.06454;,
 -1.88666;15.58446;3.85315;,
 -0.00000;16.74957;-0.06454;,
 -4.23929;15.58446;0.90305;,
 -0.00000;16.74957;-0.06454;,
 -3.39964;15.58446;-2.77566;,
 -0.00000;16.74957;-0.06454;,
 -0.00000;15.58446;-4.41284;,
 5.88835;12.40128;-4.76034;,
 -0.00000;12.40128;-7.59602;,
 7.34266;12.40128;1.61137;,
 3.26779;12.40128;6.72109;,
 -3.26779;12.40128;6.72109;,
 -7.34266;12.40128;1.61137;,
 -5.88835;12.40128;-4.76034;,
 -0.00000;12.40128;-7.59602;,
 6.79928;8.05297;-5.48678;,
 -0.00000;8.05297;-8.76114;,
 8.47857;8.05297;1.87064;,
 3.77331;8.05297;7.77083;,
 -3.77332;8.05297;7.77083;,
 -8.47857;8.05297;1.87064;,
 -6.79928;8.05297;-5.48679;,
 -0.00000;8.05297;-8.76114;,
 5.88835;3.70467;-4.76034;,
 -0.00000;3.70467;-7.59602;,
 7.34265;3.70467;1.61137;,
 3.26779;3.70467;6.72109;,
 -3.26779;3.70467;6.72109;,
 -7.34266;3.70467;1.61137;,
 -5.88835;3.70467;-4.76034;,
 -0.00000;3.70467;-7.59602;,
 3.39964;0.52148;-2.77566;,
 -0.00000;0.52148;-4.41284;,
 4.23928;0.52148;0.90305;,
 1.88666;0.52148;3.85315;,
 -1.88666;0.52148;3.85315;,
 -4.23929;0.52148;0.90305;,
 -3.39964;0.52148;-2.77566;,
 -0.00000;0.52148;-4.41284;,
 -0.00000;0.52148;-4.41284;,
 3.39964;0.52148;-2.77566;,
 -0.00000;-0.64363;-0.06454;,
 4.23928;0.52148;0.90305;,
 -0.00000;-0.64363;-0.06454;,
 1.88666;0.52148;3.85315;,
 -0.00000;-0.64363;-0.06454;,
 -1.88666;0.52148;3.85315;,
 -0.00000;-0.64363;-0.06454;,
 -4.23929;0.52148;0.90305;,
 -0.00000;-0.64363;-0.06454;,
 -3.39964;0.52148;-2.77566;,
 -0.00000;-0.64363;-0.06454;,
 -0.00000;0.52148;-4.41284;,
 -0.00000;-0.64363;-0.06454;;
 
 42;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 4;2,1,15,16;,
 4;1,4,17,15;,
 4;4,6,18,17;,
 4;6,8,19,18;,
 4;8,10,20,19;,
 4;10,12,21,20;,
 4;12,14,22,21;,
 4;16,15,23,24;,
 4;15,17,25,23;,
 4;17,18,26,25;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;24,23,31,32;,
 4;23,25,33,31;,
 4;25,26,34,33;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;32,31,39,40;,
 4;31,33,41,39;,
 4;33,34,42,41;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 3;47,48,49;,
 3;48,50,51;,
 3;50,52,53;,
 3;52,54,55;,
 3;54,56,57;,
 3;56,58,59;,
 3;58,60,61;;
 
 MeshMaterialList {
  1;
  42;
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
 }
 MeshNormals {
  37;
  0.000000;1.000000;0.000000;,
  0.000000;0.869166;-0.494520;,
  0.386631;0.869166;-0.308328;,
  0.482121;0.869166;0.110041;,
  0.214564;0.869166;0.445547;,
  -0.214564;0.869166;0.445547;,
  -0.482121;0.869166;0.110041;,
  -0.386631;0.869166;-0.308328;,
  0.000000;0.504989;-0.863126;,
  0.674819;0.504989;-0.538150;,
  0.841485;0.504989;0.192064;,
  0.374496;0.504989;0.777650;,
  -0.374496;0.504989;0.777649;,
  -0.841485;0.504989;0.192063;,
  -0.674819;0.504989;-0.538150;,
  0.000000;-0.000000;-1.000000;,
  0.781831;-0.000000;-0.623490;,
  0.974928;-0.000000;0.222521;,
  0.433883;-0.000000;0.900969;,
  -0.433884;0.000000;0.900969;,
  -0.974928;-0.000000;0.222521;,
  -0.781831;-0.000000;-0.623490;,
  0.000000;-0.504989;-0.863126;,
  0.674819;-0.504989;-0.538150;,
  0.841485;-0.504989;0.192064;,
  0.374496;-0.504989;0.777650;,
  -0.374496;-0.504989;0.777649;,
  -0.841485;-0.504989;0.192063;,
  -0.674819;-0.504989;-0.538150;,
  0.000000;-0.869166;-0.494520;,
  0.386631;-0.869166;-0.308328;,
  0.482121;-0.869166;0.110041;,
  0.214564;-0.869166;0.445547;,
  -0.214564;-0.869166;0.445547;,
  -0.482121;-0.869166;0.110041;,
  -0.386631;-0.869166;-0.308328;,
  0.000000;-1.000000;0.000000;;
  42;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,1,7;,
  4;1,2,9,8;,
  4;2,3,10,9;,
  4;3,4,11,10;,
  4;4,5,12,11;,
  4;5,6,13,12;,
  4;6,7,14,13;,
  4;7,1,8,14;,
  4;8,9,16,15;,
  4;9,10,17,16;,
  4;10,11,18,17;,
  4;11,12,19,18;,
  4;12,13,20,19;,
  4;13,14,21,20;,
  4;14,8,15,21;,
  4;15,16,23,22;,
  4;16,17,24,23;,
  4;17,18,25,24;,
  4;18,19,26,25;,
  4;19,20,27,26;,
  4;20,21,28,27;,
  4;21,15,22,28;,
  4;22,23,30,29;,
  4;23,24,31,30;,
  4;24,25,32,31;,
  4;25,26,33,32;,
  4;26,27,34,33;,
  4;27,28,35,34;,
  4;28,22,29,35;,
  3;29,30,36;,
  3;30,31,36;,
  3;31,32,36;,
  3;32,33,36;,
  3;33,34,36;,
  3;34,35,36;,
  3;35,29,36;;
 }
 MeshTextureCoords {
  62;
  0.071429;0.000000;,
  0.142857;0.166667;,
  0.000000;0.166667;,
  0.214286;0.000000;,
  0.285714;0.166667;,
  0.357143;0.000000;,
  0.428571;0.166667;,
  0.500000;0.000000;,
  0.571429;0.166667;,
  0.642857;0.000000;,
  0.714286;0.166667;,
  0.785714;0.000000;,
  0.857143;0.166667;,
  0.928571;0.000000;,
  1.000000;0.166667;,
  0.142857;0.333333;,
  0.000000;0.333333;,
  0.285714;0.333333;,
  0.428571;0.333333;,
  0.571429;0.333333;,
  0.714286;0.333333;,
  0.857143;0.333333;,
  1.000000;0.333333;,
  0.142857;0.500000;,
  0.000000;0.500000;,
  0.285714;0.500000;,
  0.428571;0.500000;,
  0.571429;0.500000;,
  0.714286;0.500000;,
  0.857143;0.500000;,
  1.000000;0.500000;,
  0.142857;0.666667;,
  0.000000;0.666667;,
  0.285714;0.666667;,
  0.428571;0.666667;,
  0.571429;0.666667;,
  0.714286;0.666667;,
  0.857143;0.666667;,
  1.000000;0.666667;,
  0.142857;0.833333;,
  0.000000;0.833333;,
  0.285714;0.833333;,
  0.428571;0.833333;,
  0.571429;0.833333;,
  0.714286;0.833333;,
  0.857143;0.833333;,
  1.000000;0.833333;,
  0.000000;0.833333;,
  0.142857;0.833333;,
  0.071429;1.000000;,
  0.285714;0.833333;,
  0.214286;1.000000;,
  0.428571;0.833333;,
  0.357143;1.000000;,
  0.571429;0.833333;,
  0.500000;1.000000;,
  0.714286;0.833333;,
  0.642857;1.000000;,
  0.857143;0.833333;,
  0.785714;1.000000;,
  1.000000;0.833333;,
  0.928571;1.000000;;
 }
}
