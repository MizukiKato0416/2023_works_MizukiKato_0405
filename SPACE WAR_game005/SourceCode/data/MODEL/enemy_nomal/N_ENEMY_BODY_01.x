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
 16;
 4.28144;-8.08662;-11.36078;,
 -4.15670;-8.08662;-11.36078;,
 -6.04010;0.07694;-13.95501;,
 6.16484;0.07694;-13.95501;,
 -6.19420;-5.91346;11.43082;,
 6.31894;-5.91346;11.43082;,
 7.73854;0.07694;11.43082;,
 -7.61380;0.07694;11.43082;,
 9.49202;-1.85986;-4.02867;,
 9.49202;-6.14984;-4.02867;,
 9.46890;-6.14984;2.39222;,
 9.46890;-1.85986;2.39222;,
 -9.34416;-1.85986;2.39222;,
 -9.34416;-6.14984;2.39222;,
 -9.45614;-6.14984;-4.02867;,
 -9.45614;-1.85986;-4.02867;;
 
 8;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,0,3;,
 4;10,11,6,5;,
 4;10,9,8,11;,
 4;12,13,4,7;,
 4;14,15,2,1;,
 4;14,13,12,15;;
 
 MeshMaterialList {
  3;
  8;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.023550;0.117000;0.004650;1.000000;;
   0.000000;
   0.060000;0.060000;0.060000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.012800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.016000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   0.000000;
   0.060000;0.060000;0.060000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  -0.494787;-0.267425;-0.826843;,
  0.000000;-0.302856;-0.953036;,
  0.000000;0.000000;1.000000;,
  -0.966501;-0.084152;-0.242476;,
  0.965832;-0.083517;-0.245345;,
  0.987900;-0.057201;0.144160;,
  -0.986878;-0.057147;0.151014;,
  0.863950;-0.161178;-0.477088;,
  0.952911;-0.113077;0.281378;,
  -0.952911;-0.113077;0.281378;;
  8;
  4;1,0,0,1;,
  4;2,2,2,2;,
  4;4,4,7,7;,
  4;5,5,8,8;,
  4;5,4,4,5;,
  4;6,6,9,9;,
  4;3,3,0,0;,
  4;3,6,6,3;;
 }
 MeshTextureCoords {
  16;
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
