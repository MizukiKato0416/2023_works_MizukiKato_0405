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
 35;
 -8.28483;19.77850;-10.63260;,
 6.50752;15.98196;-5.52654;,
 6.50752;0.20384;-5.52654;,
 -8.28483;0.20384;-10.63260;,
 -9.23582;0.20384;10.13905;,
 1.85977;0.20384;5.20953;,
 1.88686;12.81130;5.20953;,
 -9.23582;15.15455;10.13905;,
 -9.23582;15.15455;10.13905;,
 1.88686;12.81130;5.20953;,
 6.50752;15.98196;-5.52654;,
 -8.28483;19.77850;-10.63260;,
 -8.28483;19.77850;-10.63260;,
 -8.28483;0.20384;-10.63260;,
 -9.23582;0.20384;10.13905;,
 5.62159;13.44030;-4.90334;,
 18.23373;13.56687;-4.85334;,
 18.23374;1.51933;-4.85334;,
 5.62159;1.51933;-4.90334;,
 5.62159;1.51933;-4.90334;,
 18.23374;1.51933;-4.85334;,
 18.19803;1.51933;4.66566;,
 1.83252;1.51932;5.16028;,
 1.83252;1.51932;5.16028;,
 18.19803;1.51933;4.66566;,
 18.19801;13.39120;4.66566;,
 1.83252;12.53836;5.16028;,
 1.83252;12.53836;5.16028;,
 18.19801;13.39120;4.66566;,
 18.23373;13.56687;-4.85334;,
 5.62159;13.44030;-4.90334;,
 1.85610;12.80689;5.25955;,
 3.30118;13.79104;1.96269;,
 -0.65294;15.43879;1.96269;,
 -1.23758;13.47392;6.60552;;
 
 9;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,12,13,14;,
 4;15,16,17,18;,
 4;19,20,21,22;,
 4;23,24,25,26;,
 4;27,28,29,30;,
 4;31,32,33,34;;
 
 MeshMaterialList {
  3;
  9;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1;;
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
  9;
  0.326290;0.000000;-0.945270;,
  0.405598;-0.000436;0.914051;,
  0.003964;0.000000;-0.999992;,
  0.000000;-1.000000;-0.000001;,
  0.030210;0.000000;0.999544;,
  0.354109;0.843498;0.403877;,
  0.210900;0.937475;0.276879;,
  -0.998954;0.000000;-0.045735;,
  -0.029962;0.998560;0.044502;;
  9;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  35;
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
  1.000000;0.000000;;
 }
}
