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
 92;
 2.85531;-0.90308;-3.85376;,
 2.64015;-6.95579;-3.85376;,
 1.04798;-6.95579;-4.56884;,
 1.17335;-0.90308;-4.56884;,
 -1.10540;-6.95579;-4.56884;,
 -1.10147;-0.90308;-4.56884;,
 -2.69152;-6.95579;-3.73604;,
 -2.77704;-0.90308;-3.73604;,
 2.45847;-12.90648;-3.54637;,
 0.93618;-12.90648;-4.26145;,
 -1.12267;-12.90648;-4.26145;,
 -2.63917;-12.90648;-3.42865;,
 2.16872;-18.54879;-2.98696;,
 0.74201;-18.54879;-3.70204;,
 -1.18759;-18.54879;-3.70204;,
 -2.60888;-18.54879;-2.86924;,
 -2.77704;-0.90308;-3.73604;,
 -2.69152;-6.95579;-3.73604;,
 -3.25878;-6.95579;-1.86534;,
 -3.37629;-0.90308;-1.86534;,
 -3.25878;-6.95579;0.83816;,
 -3.37629;-0.90308;0.83816;,
 -2.78393;-6.95579;2.68073;,
 -2.87466;-0.90308;3.20634;,
 -2.63917;-12.90648;-3.42865;,
 -3.18153;-12.90648;-1.86534;,
 -3.18153;-12.90648;0.46854;,
 -2.72752;-12.90648;1.88231;,
 -2.60888;-18.54879;-2.86924;,
 -3.11719;-18.54879;-1.30593;,
 -3.11719;-18.54879;0.09980;,
 -2.69169;-18.54879;1.51357;,
 -2.87466;-0.90308;3.20634;,
 -2.78393;-6.95579;2.68073;,
 -1.10540;-6.95579;3.54166;,
 -1.10147;-0.90308;4.06726;,
 1.04798;-6.95579;3.54166;,
 1.17335;-0.90308;4.06726;,
 2.60665;-6.95579;2.98014;,
 2.81992;-0.90308;3.50575;,
 -2.72752;-12.90648;1.88231;,
 -1.12267;-12.90648;2.74324;,
 0.93618;-12.90648;2.74324;,
 2.42643;-12.90648;2.18172;,
 -2.69169;-18.54879;1.51357;,
 -1.18759;-18.54879;2.37450;,
 0.74201;-18.54879;2.37450;,
 2.13870;-18.54879;1.81299;,
 2.81992;-0.90308;3.50575;,
 2.60665;-6.95579;2.98014;,
 3.20136;-6.95579;0.83816;,
 3.44817;-0.90308;0.83816;,
 3.20136;-6.95579;-1.86534;,
 3.44817;-0.90308;-1.86534;,
 2.64015;-6.95579;-3.85376;,
 2.85531;-0.90308;-3.85376;,
 2.42643;-12.90648;2.18172;,
 2.99504;-12.90648;0.46854;,
 2.99504;-12.90648;-1.86534;,
 2.45847;-12.90648;-3.54637;,
 2.13870;-18.54879;1.81299;,
 2.67161;-18.54879;0.09980;,
 2.67161;-18.54879;-1.30593;,
 2.16872;-18.54879;-2.98696;,
 3.44817;-0.90308;0.83816;,
 1.45955;0.99107;1.47656;,
 1.17335;-0.90308;4.06726;,
 -1.38767;0.99107;1.47656;,
 -1.10147;-0.90308;4.06726;,
 -3.37629;-0.90308;0.83816;,
 3.44817;-0.90308;-1.86534;,
 1.45955;0.99107;-1.90720;,
 -1.38767;0.99107;-1.90720;,
 -3.37629;-0.90308;-1.86534;,
 2.85531;-0.90308;-3.85376;,
 1.17335;-0.90308;-4.56884;,
 -1.10147;-0.90308;-4.56884;,
 -2.77704;-0.90308;-3.73604;,
 2.67161;-18.54879;0.09980;,
 0.74201;-18.54879;2.37450;,
 0.74201;-20.18087;0.09980;,
 -1.18759;-18.54879;2.37450;,
 -1.18759;-20.22640;0.09980;,
 -3.11719;-18.54879;0.09980;,
 2.67161;-18.54879;-1.30593;,
 0.74201;-20.18087;-1.30593;,
 -1.18759;-20.18087;-1.30593;,
 -3.11719;-18.54879;-1.30593;,
 2.16872;-18.54879;-2.98696;,
 0.74201;-18.54879;-3.70204;,
 -1.18759;-18.54879;-3.70204;,
 -2.60888;-18.54879;-2.86924;;
 
 54;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;17,24,25,18;,
 4;18,25,26,20;,
 4;20,26,27,22;,
 4;24,28,29,25;,
 4;25,29,30,26;,
 4;26,30,31,27;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;33,40,41,34;,
 4;34,41,42,36;,
 4;36,42,43,38;,
 4;40,44,45,41;,
 4;41,45,46,42;,
 4;42,46,47,43;,
 4;48,49,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;49,56,57,50;,
 4;50,57,58,52;,
 4;52,58,59,54;,
 4;56,60,61,57;,
 4;57,61,62,58;,
 4;58,62,63,59;,
 4;48,64,65,66;,
 4;66,65,67,68;,
 4;68,67,69,23;,
 4;64,70,71,65;,
 4;65,71,72,67;,
 4;67,72,73,69;,
 4;70,74,75,71;,
 4;71,75,76,72;,
 4;72,76,77,73;,
 4;78,60,79,80;,
 4;80,79,81,82;,
 4;82,81,31,83;,
 4;84,78,80,85;,
 4;85,80,82,86;,
 4;86,82,83,87;,
 4;88,84,85,89;,
 4;89,85,86,90;,
 4;90,86,87,91;;
 
 MeshMaterialList {
  1;
  54;
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
  60;
  0.723147;0.285356;-0.628992;,
  0.150973;0.302928;-0.940979;,
  -0.279016;0.460517;-0.842659;,
  0.752342;-0.039382;-0.657595;,
  0.208994;-0.030657;-0.977436;,
  -0.238893;-0.026135;-0.970694;,
  0.754547;-0.077535;-0.651650;,
  0.218047;-0.080652;-0.972600;,
  -0.248990;-0.072725;-0.965772;,
  0.707609;-0.376603;-0.597879;,
  0.258530;-0.524710;-0.811074;,
  -0.281539;-0.517582;-0.807988;,
  -0.734442;0.286259;-0.615346;,
  -0.889419;0.410761;-0.200521;,
  -0.897287;0.406019;0.173278;,
  -0.765866;-0.022636;-0.642601;,
  -0.988012;-0.016757;-0.153466;,
  -0.991541;-0.023979;0.127559;,
  -0.768743;-0.050693;-0.637545;,
  -0.987087;-0.020696;-0.158840;,
  -0.989150;-0.022556;0.145167;,
  -0.728258;-0.344784;-0.592254;,
  -0.869941;-0.450558;-0.200502;,
  -0.875642;-0.443891;0.190293;,
  -0.762961;0.257751;0.592836;,
  -0.228624;-0.085886;0.969719;,
  0.167096;-0.089963;0.981828;,
  -0.778131;-0.072059;0.623954;,
  -0.233071;-0.107933;0.966451;,
  0.170592;-0.112580;0.978889;,
  -0.774026;-0.065049;0.629803;,
  -0.243812;-0.096375;0.965022;,
  0.179107;-0.103605;0.978359;,
  -0.736106;-0.326388;0.592975;,
  -0.281071;-0.492711;0.823551;,
  0.234347;-0.500788;0.833242;,
  0.720122;0.259100;0.643654;,
  0.968474;0.232106;0.090475;,
  0.892912;0.405429;-0.195797;,
  0.729730;-0.092666;0.677427;,
  0.989651;-0.045628;0.136045;,
  0.988993;-0.037944;-0.143017;,
  0.725000;-0.094308;0.682261;,
  0.986974;-0.056137;0.150769;,
  0.987675;-0.053344;-0.147147;,
  0.681836;-0.367487;0.632497;,
  0.856501;-0.476690;0.197920;,
  0.858752;-0.476479;-0.188450;,
  0.321287;0.907037;0.272137;,
  -0.332333;0.904233;0.268174;,
  0.321056;0.907588;-0.270569;,
  -0.326002;0.905476;-0.271729;,
  0.302821;-0.915942;0.263343;,
  -0.308652;-0.914965;0.259949;,
  0.304521;-0.916631;-0.258950;,
  -0.305189;-0.915073;-0.263630;,
  0.482479;0.777872;0.402652;,
  0.249779;0.820617;0.514003;,
  -0.271132;0.817139;0.508696;,
  0.482557;0.774979;-0.408101;;
  54;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;2,5,15,12;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;5,8,18,15;,
  4;6,9,10,7;,
  4;7,10,11,8;,
  4;8,11,21,18;,
  4;12,15,16,13;,
  4;13,16,17,14;,
  4;14,17,27,24;,
  4;15,18,19,16;,
  4;16,19,20,17;,
  4;17,20,30,27;,
  4;18,21,22,19;,
  4;19,22,23,20;,
  4;20,23,33,30;,
  4;24,27,28,25;,
  4;25,28,29,26;,
  4;26,29,39,36;,
  4;27,30,31,28;,
  4;28,31,32,29;,
  4;29,32,42,39;,
  4;30,33,34,31;,
  4;31,34,35,32;,
  4;32,35,45,42;,
  4;36,39,40,37;,
  4;37,40,41,38;,
  4;38,41,3,0;,
  4;39,42,43,40;,
  4;40,43,44,41;,
  4;41,44,6,3;,
  4;42,45,46,43;,
  4;43,46,47,44;,
  4;44,47,9,6;,
  4;36,56,48,57;,
  4;57,48,49,58;,
  4;58,49,14,24;,
  4;37,38,50,48;,
  4;48,50,51,49;,
  4;49,51,13,14;,
  4;38,0,59,50;,
  4;50,1,2,51;,
  4;51,2,12,13;,
  4;46,45,35,52;,
  4;52,35,34,53;,
  4;53,34,33,23;,
  4;47,46,52,54;,
  4;54,52,53,55;,
  4;55,53,23,22;,
  4;9,47,54,10;,
  4;10,54,55,11;,
  4;11,55,22,21;;
 }
 MeshTextureCoords {
  92;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;1.000000;,
  0.333330;0.666670;,
  0.666670;1.000000;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;;
 }
}