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
 432;
 -49.73202;43.95424;-0.06702;,
 -45.47066;43.95424;-0.06702;,
 -45.47066;-0.24694;-0.06702;,
 -49.73202;-0.24694;-0.06702;,
 -45.47066;43.95424;-0.06702;,
 -45.47066;43.95424;49.81762;,
 -45.47066;-0.24694;49.81762;,
 -45.47066;-0.24694;-0.06702;,
 -45.47066;43.95424;49.81762;,
 -49.73202;43.95424;49.81762;,
 -49.73202;-0.24694;49.81762;,
 -45.47066;-0.24694;49.81762;,
 -49.73202;43.95424;49.81762;,
 -49.73202;43.95424;-0.06702;,
 -49.73202;-0.24694;-0.06702;,
 -49.73202;-0.24694;49.81762;,
 0.32626;43.95424;-0.06702;,
 4.58762;43.95424;-0.06702;,
 4.58762;-0.24694;-0.06702;,
 0.32626;-0.24694;-0.06702;,
 4.58762;43.95424;-0.06702;,
 4.58762;43.95424;49.81762;,
 4.58762;-0.24694;49.81762;,
 4.58762;-0.24694;-0.06702;,
 4.58762;43.95424;49.81762;,
 0.32626;43.95424;49.81762;,
 0.32626;-0.24694;49.81762;,
 4.58762;-0.24694;49.81762;,
 0.32626;43.95424;49.81762;,
 0.32626;43.95424;-0.06702;,
 0.32626;-0.24694;-0.06702;,
 0.32626;-0.24694;49.81762;,
 4.34470;44.11094;-0.06702;,
 4.34470;39.84958;-0.06702;,
 -49.53811;39.84959;-0.06702;,
 -49.53811;44.11094;-0.06702;,
 4.34470;39.84958;-0.06702;,
 4.34470;39.84958;49.81762;,
 -49.53811;39.84959;49.81762;,
 -49.53811;39.84959;-0.06702;,
 4.34470;39.84958;49.81762;,
 4.34470;44.11094;49.81762;,
 -49.53811;44.11094;49.81762;,
 -49.53811;39.84959;49.81762;,
 4.34470;44.11094;49.81762;,
 4.34470;44.11094;-0.06702;,
 -49.53811;44.11094;-0.06702;,
 -49.53811;44.11094;49.81762;,
 4.34470;3.88841;-0.06702;,
 4.34470;-0.37295;-0.06702;,
 -49.53811;-0.37294;-0.06702;,
 -49.53811;3.88841;-0.06702;,
 4.34470;-0.37295;-0.06702;,
 4.34470;-0.37295;49.81762;,
 -49.53811;-0.37294;49.81762;,
 -49.53811;-0.37294;-0.06702;,
 4.34470;-0.37295;49.81762;,
 4.34470;3.88841;49.81762;,
 -49.53811;3.88841;49.81762;,
 -49.53811;-0.37294;49.81762;,
 4.34470;3.88841;49.81762;,
 4.34470;3.88841;-0.06702;,
 -49.53811;3.88841;-0.06702;,
 -49.53811;3.88841;49.81762;,
 -46.17961;3.53003;46.68482;,
 0.63128;3.53003;46.68482;,
 0.63128;40.52012;46.68482;,
 -46.17961;40.52012;46.68482;,
 0.63128;3.53003;3.05735;,
 -46.17961;3.53003;3.05735;,
 -46.17961;40.52012;3.05735;,
 0.63128;40.52012;3.05735;,
 0.12233;88.18225;-0.06702;,
 4.38367;88.18225;-0.06702;,
 4.38367;43.98106;-0.06702;,
 0.12233;43.98106;-0.06702;,
 4.38367;88.18225;-0.06702;,
 4.38367;88.18225;49.81762;,
 4.38367;43.98106;49.81762;,
 4.38367;43.98106;-0.06702;,
 4.38367;88.18225;49.81762;,
 0.12233;88.18225;49.81762;,
 0.12233;43.98106;49.81762;,
 4.38367;43.98106;49.81762;,
 0.12233;88.18225;49.81762;,
 0.12233;88.18225;-0.06702;,
 0.12233;43.98106;-0.06702;,
 0.12233;43.98106;49.81762;,
 50.18058;88.18225;-0.06702;,
 54.44187;88.18225;-0.06702;,
 54.44187;43.98106;-0.06702;,
 50.18058;43.98106;-0.06702;,
 54.44187;88.18225;-0.06702;,
 54.44187;88.18225;49.81762;,
 54.44187;43.98106;49.81762;,
 54.44187;43.98106;-0.06702;,
 54.44187;88.18225;49.81762;,
 50.18058;88.18225;49.81762;,
 50.18058;43.98106;49.81762;,
 54.44187;43.98106;49.81762;,
 50.18058;88.18225;49.81762;,
 50.18058;88.18225;-0.06702;,
 50.18058;43.98106;-0.06702;,
 50.18058;43.98106;49.81762;,
 54.19895;88.33895;-0.06702;,
 54.19895;84.07758;-0.06702;,
 0.31623;84.07758;-0.06702;,
 0.31623;88.33895;-0.06702;,
 54.19895;84.07758;-0.06702;,
 54.19895;84.07758;49.81762;,
 0.31623;84.07758;49.81762;,
 0.31623;84.07758;-0.06702;,
 54.19895;84.07758;49.81762;,
 54.19895;88.33895;49.81762;,
 0.31623;88.33895;49.81762;,
 0.31623;84.07758;49.81762;,
 54.19895;88.33895;49.81762;,
 54.19895;88.33895;-0.06702;,
 0.31623;88.33895;-0.06702;,
 0.31623;88.33895;49.81762;,
 54.19895;48.11641;-0.06702;,
 54.19895;43.85505;-0.06702;,
 0.31623;43.85505;-0.06702;,
 0.31623;48.11641;-0.06702;,
 54.19895;43.85505;-0.06702;,
 54.19895;43.85505;49.81762;,
 0.31623;43.85505;49.81762;,
 0.31623;43.85505;-0.06702;,
 54.19895;43.85505;49.81762;,
 54.19895;48.11641;49.81762;,
 0.31623;48.11641;49.81762;,
 0.31623;43.85505;49.81762;,
 54.19895;48.11641;49.81762;,
 54.19895;48.11641;-0.06702;,
 0.31623;48.11641;-0.06702;,
 0.31623;48.11641;49.81762;,
 3.67473;47.75803;46.68482;,
 50.48560;47.75803;46.68482;,
 50.48560;84.74812;46.68482;,
 3.67473;84.74812;46.68482;,
 50.48559;47.75803;3.05735;,
 3.67473;47.75803;3.05735;,
 3.67473;84.74812;3.05735;,
 50.48559;84.74812;3.05735;,
 0.30856;132.29833;4.36156;,
 0.30856;132.29833;0.10020;,
 0.30856;88.09715;0.10020;,
 0.30856;88.09715;4.36156;,
 0.30856;132.29833;0.10020;,
 50.19319;132.29833;0.10020;,
 50.19319;88.09715;0.10020;,
 0.30856;88.09715;0.10020;,
 50.19319;132.29833;0.10020;,
 50.19319;132.29833;4.36156;,
 50.19319;88.09715;4.36156;,
 50.19319;88.09715;0.10020;,
 50.19319;132.29833;4.36156;,
 0.30856;132.29833;4.36156;,
 0.30856;88.09715;4.36156;,
 50.19319;88.09715;4.36156;,
 0.30856;132.29833;-45.69670;,
 0.30856;132.29833;-49.95800;,
 0.30856;88.09715;-49.95800;,
 0.30856;88.09715;-45.69670;,
 0.30856;132.29833;-49.95800;,
 50.19319;132.29833;-49.95800;,
 50.19319;88.09715;-49.95800;,
 0.30856;88.09715;-49.95800;,
 50.19319;132.29833;-49.95800;,
 50.19319;132.29833;-45.69670;,
 50.19319;88.09715;-45.69670;,
 50.19319;88.09715;-49.95800;,
 50.19319;132.29833;-45.69670;,
 0.30856;132.29833;-45.69670;,
 0.30856;88.09715;-45.69670;,
 50.19319;88.09715;-45.69670;,
 0.30856;132.45504;-49.71508;,
 0.30856;128.19368;-49.71508;,
 0.30856;128.19368;4.16765;,
 0.30856;132.45504;4.16765;,
 0.30856;128.19368;-49.71508;,
 50.19319;128.19368;-49.71508;,
 50.19319;128.19368;4.16765;,
 0.30856;128.19368;4.16765;,
 50.19319;128.19368;-49.71508;,
 50.19319;132.45504;-49.71508;,
 50.19319;132.45504;4.16765;,
 50.19319;128.19368;4.16765;,
 50.19319;132.45504;-49.71508;,
 0.30856;132.45504;-49.71508;,
 0.30856;132.45504;4.16765;,
 50.19319;132.45504;4.16765;,
 0.30856;92.23251;-49.71508;,
 0.30856;87.97115;-49.71508;,
 0.30856;87.97115;4.16765;,
 0.30856;92.23251;4.16765;,
 0.30856;87.97115;-49.71508;,
 50.19319;87.97115;-49.71508;,
 50.19319;87.97115;4.16765;,
 0.30856;87.97115;4.16765;,
 50.19319;87.97115;-49.71508;,
 50.19319;92.23251;-49.71508;,
 50.19319;92.23251;4.16765;,
 50.19319;87.97115;4.16765;,
 50.19319;92.23251;-49.71508;,
 0.30856;92.23251;-49.71508;,
 0.30856;92.23251;4.16765;,
 50.19319;92.23251;4.16765;,
 47.06039;91.87413;0.80914;,
 47.06039;91.87413;-46.00172;,
 47.06039;128.86421;-46.00172;,
 47.06039;128.86421;0.80914;,
 3.43292;91.87413;-46.00172;,
 3.43293;91.87413;0.80915;,
 3.43293;128.86421;0.80915;,
 3.43292;128.86421;-46.00172;,
 -44.78473;176.86176;4.36156;,
 -44.78473;176.86176;0.10020;,
 -44.78473;132.66059;0.10020;,
 -44.78473;132.66059;4.36156;,
 -44.78473;176.86176;0.10020;,
 5.09991;176.86176;0.10020;,
 5.09991;132.66059;0.10020;,
 -44.78473;132.66059;0.10020;,
 5.09991;176.86176;0.10020;,
 5.09991;176.86176;4.36156;,
 5.09991;132.66059;4.36156;,
 5.09991;132.66059;0.10020;,
 5.09991;176.86176;4.36156;,
 -44.78473;176.86176;4.36156;,
 -44.78473;132.66059;4.36156;,
 5.09991;132.66059;4.36156;,
 -44.78473;176.86176;-45.69670;,
 -44.78473;176.86176;-49.95800;,
 -44.78473;132.66059;-49.95800;,
 -44.78473;132.66059;-45.69670;,
 -44.78473;176.86176;-49.95800;,
 5.09991;176.86176;-49.95800;,
 5.09991;132.66059;-49.95800;,
 -44.78473;132.66059;-49.95800;,
 5.09991;176.86176;-49.95800;,
 5.09991;176.86176;-45.69670;,
 5.09991;132.66059;-45.69670;,
 5.09991;132.66059;-49.95800;,
 5.09991;176.86176;-45.69670;,
 -44.78473;176.86176;-45.69670;,
 -44.78473;132.66059;-45.69670;,
 5.09991;132.66059;-45.69670;,
 -44.78473;177.01847;-49.71508;,
 -44.78473;172.75711;-49.71508;,
 -44.78473;172.75711;4.16765;,
 -44.78473;177.01847;4.16765;,
 -44.78473;172.75711;-49.71508;,
 5.09991;172.75711;-49.71508;,
 5.09991;172.75711;4.16765;,
 -44.78473;172.75711;4.16765;,
 5.09991;172.75711;-49.71508;,
 5.09991;177.01847;-49.71508;,
 5.09991;177.01847;4.16765;,
 5.09991;172.75711;4.16765;,
 5.09991;177.01847;-49.71508;,
 -44.78473;177.01847;-49.71508;,
 -44.78473;177.01847;4.16765;,
 5.09991;177.01847;4.16765;,
 -44.78473;136.79594;-49.71508;,
 -44.78473;132.53458;-49.71508;,
 -44.78473;132.53458;4.16765;,
 -44.78473;136.79594;4.16765;,
 -44.78473;132.53458;-49.71508;,
 5.09991;132.53458;-49.71508;,
 5.09991;132.53458;4.16765;,
 -44.78473;132.53458;4.16765;,
 5.09991;132.53458;-49.71508;,
 5.09991;136.79594;-49.71508;,
 5.09991;136.79594;4.16765;,
 5.09991;132.53458;4.16765;,
 5.09991;136.79594;-49.71508;,
 -44.78473;136.79594;-49.71508;,
 -44.78473;136.79594;4.16765;,
 5.09991;136.79594;4.16765;,
 1.96710;136.43756;0.80914;,
 1.96710;136.43756;-46.00172;,
 1.96710;173.42764;-46.00172;,
 1.96710;173.42764;0.80914;,
 -41.66037;136.43756;-46.00172;,
 -41.66036;136.43756;0.80915;,
 -41.66036;173.42764;0.80915;,
 -41.66037;173.42764;-46.00172;,
 7.31737;221.07259;50.04369;,
 3.05601;221.07259;50.04369;,
 3.05601;176.87143;50.04369;,
 7.31737;176.87143;50.04369;,
 3.05601;221.07259;50.04369;,
 3.05601;221.07259;0.15905;,
 3.05601;176.87143;0.15905;,
 3.05601;176.87143;50.04369;,
 3.05601;221.07259;0.15905;,
 7.31737;221.07259;0.15905;,
 7.31737;176.87143;0.15905;,
 3.05601;176.87143;0.15905;,
 7.31737;221.07259;0.15905;,
 7.31737;221.07259;50.04369;,
 7.31737;176.87143;50.04369;,
 7.31737;176.87143;0.15905;,
 -42.74089;221.07259;50.04369;,
 -47.00219;221.07259;50.04369;,
 -47.00219;176.87143;50.04369;,
 -42.74089;176.87143;50.04369;,
 -47.00219;221.07259;50.04369;,
 -47.00219;221.07259;0.15906;,
 -47.00219;176.87143;0.15906;,
 -47.00219;176.87143;50.04369;,
 -47.00219;221.07259;0.15906;,
 -42.74089;221.07259;0.15906;,
 -42.74089;176.87143;0.15906;,
 -47.00219;176.87143;0.15906;,
 -42.74089;221.07259;0.15906;,
 -42.74089;221.07259;50.04369;,
 -42.74089;176.87143;50.04369;,
 -42.74089;176.87143;0.15906;,
 -46.75927;221.22932;50.04369;,
 -46.75927;216.96795;50.04369;,
 7.12345;216.96795;50.04369;,
 7.12345;221.22932;50.04369;,
 -46.75927;216.96795;50.04369;,
 -46.75927;216.96795;0.15906;,
 7.12345;216.96795;0.15905;,
 7.12345;216.96795;50.04369;,
 -46.75927;216.96795;0.15906;,
 -46.75927;221.22932;0.15906;,
 7.12345;221.22932;0.15905;,
 7.12345;216.96795;0.15905;,
 -46.75927;221.22932;0.15906;,
 -46.75927;221.22932;50.04369;,
 7.12345;221.22932;50.04369;,
 7.12345;221.22932;0.15905;,
 -46.75927;181.00678;50.04369;,
 -46.75927;176.74542;50.04369;,
 7.12345;176.74542;50.04369;,
 7.12345;181.00678;50.04369;,
 -46.75927;176.74542;50.04369;,
 -46.75927;176.74542;0.15906;,
 7.12345;176.74542;0.15905;,
 7.12345;176.74542;50.04369;,
 -46.75927;176.74542;0.15906;,
 -46.75927;181.00678;0.15906;,
 7.12345;181.00678;0.15905;,
 7.12345;176.74542;0.15905;,
 -46.75927;181.00678;0.15906;,
 -46.75927;181.00678;50.04369;,
 7.12345;181.00678;50.04369;,
 7.12345;181.00678;0.15905;,
 3.76495;180.64840;3.29186;,
 -43.04592;180.64840;3.29186;,
 -43.04592;217.63848;3.29186;,
 3.76495;217.63848;3.29186;,
 -43.04591;180.64840;46.91933;,
 3.76496;180.64840;46.91932;,
 3.76496;217.63848;46.91932;,
 -43.04591;217.63848;46.91933;,
 52.86137;265.47600;-2.05841;,
 52.86137;265.47600;2.20295;,
 52.86137;221.27483;2.20295;,
 52.86137;221.27483;-2.05841;,
 52.86137;265.47600;2.20295;,
 2.97673;265.47600;2.20296;,
 2.97673;221.27483;2.20296;,
 52.86137;221.27483;2.20295;,
 2.97673;265.47600;2.20296;,
 2.97673;265.47600;-2.05841;,
 2.97673;221.27483;-2.05841;,
 2.97673;221.27483;2.20296;,
 2.97673;265.47600;-2.05841;,
 52.86137;265.47600;-2.05841;,
 52.86137;221.27483;-2.05841;,
 2.97673;221.27483;-2.05841;,
 52.86138;265.47600;47.99985;,
 52.86138;265.47600;52.26115;,
 52.86138;221.27483;52.26115;,
 52.86138;221.27483;47.99985;,
 52.86138;265.47600;52.26115;,
 2.97674;265.47600;52.26115;,
 2.97674;221.27483;52.26115;,
 52.86138;221.27483;52.26115;,
 2.97674;265.47600;52.26115;,
 2.97674;265.47600;47.99985;,
 2.97674;221.27483;47.99985;,
 2.97674;221.27483;52.26115;,
 2.97674;265.47600;47.99985;,
 52.86138;265.47600;47.99985;,
 52.86138;221.27483;47.99985;,
 2.97674;221.27483;47.99985;,
 52.86138;265.63274;52.01823;,
 52.86138;261.37137;52.01823;,
 52.86137;261.37137;-1.86449;,
 52.86137;265.63274;-1.86449;,
 52.86138;261.37137;52.01823;,
 2.97674;261.37137;52.01823;,
 2.97673;261.37137;-1.86449;,
 52.86137;261.37137;-1.86449;,
 2.97674;261.37137;52.01823;,
 2.97674;265.63274;52.01823;,
 2.97673;265.63274;-1.86449;,
 2.97673;261.37137;-1.86449;,
 2.97674;265.63274;52.01823;,
 52.86138;265.63274;52.01823;,
 52.86137;265.63274;-1.86449;,
 2.97673;265.63274;-1.86449;,
 52.86138;225.41018;52.01823;,
 52.86138;221.14886;52.01823;,
 52.86137;221.14886;-1.86449;,
 52.86137;225.41018;-1.86449;,
 52.86138;221.14886;52.01823;,
 2.97674;221.14886;52.01823;,
 2.97673;221.14886;-1.86449;,
 52.86137;221.14886;-1.86449;,
 2.97674;221.14886;52.01823;,
 2.97674;225.41018;52.01823;,
 2.97673;225.41018;-1.86449;,
 2.97673;221.14886;-1.86449;,
 2.97674;225.41018;52.01823;,
 52.86138;225.41018;52.01823;,
 52.86137;225.41018;-1.86449;,
 2.97673;225.41018;-1.86449;,
 6.10954;225.05183;1.49401;,
 6.10955;225.05183;48.30488;,
 6.10955;262.04190;48.30488;,
 6.10954;262.04190;1.49401;,
 49.73702;225.05183;48.30487;,
 49.73700;225.05183;1.49400;,
 49.73700;262.04190;1.49400;,
 49.73702;262.04190;48.30487;;
 
 108;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;296,297,298,299;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;316,317,318,319;,
 4;320,321,322,323;,
 4;324,325,326,327;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;336,337,338,339;,
 4;340,341,342,343;,
 4;344,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;356,357,358,359;,
 4;360,361,362,363;,
 4;364,365,366,367;,
 4;368,369,370,371;,
 4;372,373,374,375;,
 4;376,377,378,379;,
 4;380,381,382,383;,
 4;384,385,386,387;,
 4;388,389,390,391;,
 4;392,393,394,395;,
 4;396,397,398,399;,
 4;400,401,402,403;,
 4;404,405,406,407;,
 4;408,409,410,411;,
 4;412,413,414,415;,
 4;416,417,418,419;,
 4;420,421,422,423;,
 4;424,425,426,427;,
 4;428,429,430,431;;
 
 MeshMaterialList {
  2;
  108;
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
  1,
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
  1,
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
  1,
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
  1,
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
  1,
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
  1;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.062745;1.000000;0.984314;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.062745;1.000000;0.984314;;
  }
 }
 MeshNormals {
  65;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;;
  108;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;24,24,24,24;,
  4;18,18,18,18;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;24,24,24,24;,
  4;20,20,20,20;,
  4;22,22,22,22;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;32,32,32,32;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;32,32,32,32;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;27,27,27,27;,
  4;33,33,33,33;,
  4;30,30,30,30;,
  4;29,29,29,29;,
  4;27,27,27,27;,
  4;33,33,33,33;,
  4;27,27,27,27;,
  4;31,31,31,31;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;39,39,39,39;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;39,39,39,39;,
  4;34,34,34,34;,
  4;37,37,37,37;,
  4;36,36,36,36;,
  4;40,40,40,40;,
  4;34,34,34,34;,
  4;37,37,37,37;,
  4;36,36,36,36;,
  4;40,40,40,40;,
  4;36,36,36,36;,
  4;38,38,38,38;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;50,50,50,50;,
  4;41,41,41,41;,
  4;44,44,44,44;,
  4;43,43,43,43;,
  4;51,51,51,51;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;52,52,52,52;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;52,52,52,52;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;62,62,62,62;,
  4;53,53,53,53;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;63,63,63,63;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;64,64,64,64;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;64,64,64,64;,
  4;60,60,60,60;,
  4;61,61,61,61;;
 }
 MeshTextureCoords {
  432;
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
