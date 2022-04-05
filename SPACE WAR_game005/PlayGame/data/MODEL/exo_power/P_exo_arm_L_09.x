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
 96;
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
 6.55203;-2.18886;-4.72458;,
 6.55203;1.39380;-4.72458;,
 9.67228;1.13390;-6.19117;,
 9.67228;-1.38611;-6.19117;,
 9.67341;-1.40622;-6.19941;,
 9.63188;1.12932;-6.19941;,
 16.96097;1.84170;-3.52850;,
 16.96097;-0.25128;-3.52850;,
 24.02947;1.41058;-3.42836;,
 24.02947;-0.25383;-3.42836;,
 6.55203;1.39380;-4.72458;,
 7.15328;2.40287;4.04151;,
 9.50585;2.79249;3.03616;,
 9.67228;1.13390;-6.19117;,
 9.63188;1.12932;-6.19941;,
 9.48146;2.78226;3.08438;,
 20.42053;1.84170;-0.12609;,
 16.96097;1.84170;-3.52850;,
 24.49255;1.41058;-1.48852;,
 24.02947;1.41058;-3.42836;,
 7.15328;2.40287;4.04151;,
 7.15328;-2.99366;4.04151;,
 9.50585;-2.03732;3.03616;,
 9.50585;2.79249;3.03616;,
 9.48146;2.78226;3.08438;,
 9.52299;-2.03732;3.08438;,
 20.42053;-0.25128;-0.12609;,
 20.42053;1.84170;-0.12609;,
 24.49255;-0.25383;-1.48852;,
 24.49255;1.41058;-1.48852;,
 7.15328;-2.99366;4.04151;,
 6.55203;-2.18886;-4.72458;,
 9.67228;-1.38611;-6.19117;,
 9.50585;-2.03732;3.03616;,
 9.52299;-2.03732;3.08438;,
 9.67341;-1.40622;-6.19941;,
 16.96097;-0.25128;-3.52850;,
 20.42053;-0.25128;-0.12609;,
 6.55203;1.39380;-4.72458;,
 6.55203;-2.18886;-4.72458;,
 9.71166;-2.00203;3.03497;,
 9.71166;2.84996;3.03497;,
 7.91354;2.53218;3.71760;,
 7.91354;-2.75353;3.71760;,
 8.91221;-2.35511;3.34542;,
 8.91221;2.72647;3.34542;,
 8.60148;2.65919;3.46141;,
 8.60148;-2.50124;3.46141;,
 5.85483;-1.40654;-1.28892;,
 5.85483;1.22014;-1.28892;,
 7.27709;1.46291;-1.53165;,
 7.27709;-1.64926;-1.53165;,
 5.85483;1.22014;-1.28892;,
 5.85483;1.22014;1.33776;,
 7.27709;1.46291;1.58046;,
 7.27709;1.46291;-1.53165;,
 5.85483;1.22014;1.33776;,
 5.85483;-1.40654;1.33776;,
 7.27709;-1.64926;1.58046;,
 7.27709;1.46291;1.58046;,
 4.55468;3.18539;5.62100;,
 24.58324;3.18540;-0.23804;,
 23.39131;1.64595;-4.54894;,
 7.03682;1.64594;-6.71591;,
 4.55469;3.14707;5.62100;,
 7.03682;1.60763;-6.71591;,
 23.39133;1.60762;-4.54894;,
 24.58325;3.14709;-0.23804;;
 
 29;
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
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;;
 
 MeshMaterialList {
  5;
  29;
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
  1,
  2,
  2,
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
  36;
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000002;,
  0.000000;-0.960373;0.278718;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;-0.000002;,
  0.000000;-0.960372;-0.278723;,
  0.000000;0.960375;0.278710;,
  0.000000;0.960374;-0.278715;,
  0.960375;0.000000;0.278710;,
  1.000000;0.000000;-0.000002;,
  0.960374;0.000000;-0.278715;,
  -1.000000;0.000000;-0.000002;,
  -0.960375;0.000000;0.278710;,
  -0.960374;0.000000;-0.278715;,
  -0.425379;0.000000;-0.905015;,
  0.342865;0.002812;-0.939381;,
  0.181062;0.001426;-0.983471;,
  0.014166;0.000000;-0.999900;,
  -0.102849;0.985024;-0.138381;,
  0.017205;0.992419;-0.121693;,
  0.048476;0.995416;-0.082450;,
  0.079625;0.995897;-0.042998;,
  0.392964;0.000000;0.919554;,
  0.281919;0.001216;0.959437;,
  0.299658;0.000608;0.954046;,
  0.317294;0.000000;0.948327;,
  0.354920;0.000000;0.934897;,
  0.349723;0.000000;0.936853;,
  -0.168231;0.000000;-0.985748;,
  -0.168262;0.985742;0.000000;,
  -0.168212;0.000000;0.985751;,
  -0.037941;0.975234;-0.217897;,
  0.037942;-0.975234;0.217898;,
  0.277597;-0.956752;-0.086974;,
  0.151688;-0.983842;-0.095106;,
  -0.997656;0.000000;0.068427;;
  29;
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
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;;
 }
 MeshTextureCoords {
  96;
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
  0.333330;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.333330;1.000000;,
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
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}