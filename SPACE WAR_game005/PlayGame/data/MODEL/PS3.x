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
 158;
 -45.32280;94.30234;4.02798;,
 -45.32280;-13.09484;4.02798;,
 -15.10760;-13.09484;17.00711;,
 -15.10760;94.30234;17.00711;,
 15.10760;-13.09484;17.00711;,
 15.10760;94.30234;17.00711;,
 45.32280;-13.09484;4.02798;,
 45.32280;94.30234;4.02798;,
 45.32280;94.30234;4.02798;,
 45.32280;-13.09484;4.02798;,
 45.32280;-13.09484;-0.16484;,
 45.32280;94.30234;-0.16484;,
 45.32280;94.30234;-0.16484;,
 45.32280;-13.09484;-0.16484;,
 15.10760;-13.09484;-0.16484;,
 15.10760;94.30234;-0.16484;,
 -45.32280;94.30234;-0.16484;,
 -45.32280;-13.09484;-0.16484;,
 -45.32280;-13.09484;4.02798;,
 -45.32280;94.30234;4.02798;,
 -45.32280;94.30234;4.02798;,
 -15.10760;94.30234;17.00711;,
 -15.10760;94.30234;-0.16484;,
 15.10760;94.30234;17.00711;,
 15.10760;94.30234;-0.16484;,
 45.32280;94.30234;4.02798;,
 -45.32280;-13.09484;4.02798;,
 -15.10760;-13.09484;-0.16484;,
 -15.10760;-13.09484;17.00711;,
 15.10760;-13.09484;-0.16484;,
 15.10760;-13.09484;17.00711;,
 45.32280;-13.09484;4.02798;,
 -45.32280;94.30234;-4.26290;,
 -15.10760;94.30234;-17.24203;,
 -15.10760;-13.09484;-17.24203;,
 -45.32280;-13.09484;-4.26290;,
 15.10760;94.30234;-17.24203;,
 15.10760;-13.09484;-17.24203;,
 45.32280;94.30234;-0.07008;,
 15.10760;94.30234;-0.07008;,
 15.10760;-13.09484;-0.07008;,
 45.32280;-13.09484;-0.07008;,
 -45.32280;94.30234;-0.07008;,
 -45.32280;94.30234;-4.26290;,
 -45.32280;-13.09484;-4.26290;,
 -45.32280;-13.09484;-0.07008;,
 -15.10760;94.30234;-0.07008;,
 -15.10760;94.30234;-17.24203;,
 -45.32280;94.30234;-4.26290;,
 15.10760;94.30234;-0.07008;,
 15.10760;94.30234;-17.24203;,
 -45.32280;-13.09484;-4.26290;,
 -15.10760;-13.09484;-17.24203;,
 -15.10760;-13.09484;-0.07008;,
 15.10760;-13.09484;-17.24203;,
 15.10760;-13.09484;-0.07008;,
 45.32280;-13.09484;-4.26290;,
 45.32280;-13.09484;-0.07008;,
 15.10760;94.30234;-17.24203;,
 35.28083;94.30234;-8.71842;,
 35.28083;-13.09484;-8.71842;,
 15.10760;-13.09484;-17.24203;,
 15.10760;94.30234;-0.07008;,
 35.30227;94.30234;-0.07008;,
 35.30227;94.30234;-8.79558;,
 15.10760;94.30234;-17.24203;,
 15.10760;13.85163;-0.07008;,
 45.29160;13.85163;-0.07008;,
 45.29160;13.85163;-4.15099;,
 15.10760;13.85163;-17.24203;,
 35.27487;13.74145;-8.64277;,
 45.16858;13.74145;-4.15261;,
 45.16858;-13.09484;-4.15261;,
 35.27487;-13.09484;-8.64277;,
 45.32280;13.92488;-4.26290;,
 45.32280;13.92488;-0.07008;,
 45.32280;-13.09484;-0.07008;,
 45.32280;-13.09484;-4.26290;,
 35.09482;94.24935;0.36046;,
 35.09482;11.32425;0.36046;,
 35.09482;11.32425;-8.70155;,
 35.09482;94.24935;-8.70155;,
 35.15859;88.46094;-2.76206;,
 35.15859;18.22312;-2.76206;,
 35.15859;18.22312;-6.03352;,
 35.15859;88.46094;-6.03352;,
 37.98559;54.51718;-0.18014;,
 42.12133;54.51718;-0.18014;,
 42.12133;50.38144;-0.18014;,
 37.98559;50.38144;-0.18014;,
 14.38597;81.11045;6.29142;,
 39.62768;81.11045;6.29142;,
 39.62768;-12.62258;6.29142;,
 14.38597;-12.62258;6.29142;,
 39.62768;81.11045;6.29142;,
 39.62768;81.11045;17.06930;,
 39.62768;-12.62258;17.06930;,
 39.62768;-12.62258;6.29142;,
 39.62768;81.11045;17.06930;,
 14.38597;81.11045;17.06930;,
 14.38597;-12.62258;17.06930;,
 39.62768;-12.62258;17.06930;,
 14.38597;81.11045;17.06930;,
 14.38597;81.11045;6.29142;,
 14.38597;-12.62258;6.29142;,
 14.38597;-12.62258;17.06930;,
 39.62768;81.11045;6.29142;,
 14.38597;81.11045;6.29142;,
 14.38597;-12.62258;6.29142;,
 39.62768;-12.62258;6.29142;,
 39.65796;76.70511;14.28874;,
 39.65796;18.84277;14.28874;,
 39.65796;18.84277;8.24681;,
 39.65796;76.70511;8.24681;,
 39.67051;71.87410;17.01366;,
 39.67051;70.20559;17.01366;,
 39.67051;70.20559;3.85898;,
 39.67051;71.87410;3.85898;,
 39.67051;65.34821;17.01366;,
 39.67051;63.67969;17.01366;,
 39.67051;63.67969;3.85898;,
 39.67051;65.34821;3.85898;,
 39.67051;58.87173;17.01366;,
 39.67051;57.20322;17.01366;,
 39.67051;57.20322;3.85898;,
 39.67051;58.87173;3.85898;,
 39.67051;52.35167;17.01366;,
 39.67051;50.68316;17.01366;,
 39.67051;50.68316;3.85898;,
 39.67051;52.35167;3.85898;,
 39.67051;45.88765;17.01366;,
 39.67051;44.21914;17.01366;,
 39.67051;44.21914;3.85898;,
 39.67051;45.88765;3.85898;,
 39.67051;39.37677;17.01366;,
 39.67051;37.70826;17.01366;,
 39.67051;37.70826;3.85898;,
 39.67051;39.37677;3.85898;,
 39.67051;32.85372;17.01366;,
 39.67051;31.18521;17.01366;,
 39.67051;31.18521;3.85898;,
 39.67051;32.85372;3.85898;,
 39.67051;26.42347;17.01366;,
 39.67051;24.75496;17.01366;,
 39.67051;24.75496;3.85898;,
 39.67051;26.42347;3.85898;,
 -10.00000;0.00000;10.00000;,
 10.00000;0.00000;10.00000;,
 10.00000;0.00000;-10.00000;,
 -10.00000;0.00000;-10.00000;,
 39.62830;13.65630;15.60483;,
 39.62830;5.42496;15.60483;,
 39.62830;5.42496;12.30052;,
 39.62830;13.65630;12.30052;,
 39.62830;0.50557;15.60483;,
 39.62830;-7.72577;15.60483;,
 39.62830;-7.72577;12.30052;,
 39.62830;0.50557;12.30052;;
 
 47;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;16,20,21,22;,
 4;22,21,23,24;,
 4;24,23,25,11;,
 4;26,17,27,28;,
 4;28,27,29,30;,
 4;30,29,10,31;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;42,46,47,48;,
 4;46,49,50,47;,
 4;51,52,53,45;,
 4;52,54,55,53;,
 4;54,56,57,55;,
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
 4;102,95,106,107;,
 4;108,109,96,105;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 4;150,151,152,153;,
 4;154,155,156,157;;
 
 MeshMaterialList {
  3;
  47;
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
  1,
  0,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
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
  2;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.741000;0.741000;0.741000;1.000000;;
   10.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.055000;1.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.055000;1.000000;;
  }
 }
 MeshNormals {
  42;
  -0.394684;0.000000;0.918817;,
  -0.201473;0.000000;0.979494;,
  0.201473;0.000000;0.979494;,
  0.394684;0.000000;0.918817;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.394684;0.000000;-0.918817;,
  -0.201473;0.000000;-0.979494;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.389206;0.000000;-0.921151;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.413270;0.000000;-0.910608;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  47;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;8,8,8,8;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;13,13,13,13;,
  4;15,15,15,15;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;;
 }
 MeshTextureCoords {
  158;
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
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