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
 17;
 -56.16099;0.24921;-10.65569;,
 -56.16102;9.23461;-5.46795;,
 0.08363;9.23460;-5.46795;,
 0.08363;0.24921;-10.65569;,
 -56.16102;9.23461;4.90753;,
 0.08363;9.23460;4.90753;,
 -56.16099;0.24921;10.09527;,
 0.08363;0.24921;10.09527;,
 -56.16102;-8.73626;4.90753;,
 0.08363;-8.73627;4.90753;,
 -56.16102;-8.73626;-5.46795;,
 0.08363;-8.73627;-5.46795;,
 -80.99868;0.24921;-0.28021;,
 0.08363;0.24921;-0.28021;,
 0.08363;0.24921;-10.65569;,
 0.08363;9.23460;-5.46795;,
 0.08363;-8.73627;-5.46795;;
 
 18;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,0,3,11;,
 3;12,1,0;,
 3;12,4,1;,
 3;12,6,4;,
 3;12,8,6;,
 3;12,10,8;,
 3;12,0,10;,
 3;13,14,15;,
 3;13,15,5;,
 3;13,5,7;,
 3;13,7,9;,
 3;13,9,16;,
 3;13,16,14;;
 
 MeshMaterialList {
  8;
  18;
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
   0.448627;0.401569;0.282353;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.316863;0.316863;0.316863;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.006275;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Visual Studio 2015\\Projects\\3Dgame_11.08_Ver_01\\data\\TEXTURE\\gear.png";
   }
  }
  Material {
   0.483137;0.483137;0.483137;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Visual Studio 2015\\Projects\\3Dgame_11.08_Ver_01\\data\\TEXTURE\\gear.png";
   }
  }
 }
 MeshNormals {
  18;
  -0.385452;0.799106;-0.461364;,
  -0.258328;0.189843;-0.947220;,
  -0.258327;0.725397;-0.638017;,
  -0.258327;0.915238;0.309203;,
  -0.258328;0.189843;0.947221;,
  -0.258329;-0.725395;0.638019;,
  -0.258329;-0.915237;-0.309204;,
  0.000000;0.500001;-0.866025;,
  0.000000;1.000000;0.000000;,
  0.000000;0.500001;0.866025;,
  -0.000000;-0.499998;0.866027;,
  -0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.000000;-0.499998;-0.866027;,
  -0.385452;0.000002;0.922728;,
  -0.385454;-0.799104;-0.461365;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000001;0.000000;;
  18;
  4;1,2,7,7;,
  4;8,3,8,8;,
  4;9,4,9,9;,
  4;10,5,10,10;,
  4;11,6,11,11;,
  4;13,13,13,13;,
  3;0,2,1;,
  3;0,3,2;,
  3;14,4,3;,
  3;14,5,4;,
  3;15,6,5;,
  3;15,1,6;,
  3;12,12,16;,
  3;12,16,16;,
  3;12,16,12;,
  3;12,12,17;,
  3;12,17,17;,
  3;12,17,12;;
 }
 MeshTextureCoords {
  17;
  0.779842;0.498612;,
  0.765447;0.448364;,
  1.002434;0.170185;,
  1.001249;0.492557;,
  0.736128;0.448318;,
  0.497288;0.155505;,
  0.721693;0.498610;,
  0.498682;0.492144;,
  0.736128;0.548938;,
  0.497288;0.837065;,
  0.765447;0.548894;,
  1.002434;0.821972;,
  0.750551;0.499021;,
  0.046159;0.275338;,
  0.001249;0.492557;,
  0.002434;0.170185;,
  0.002434;0.821972;;
 }
}
