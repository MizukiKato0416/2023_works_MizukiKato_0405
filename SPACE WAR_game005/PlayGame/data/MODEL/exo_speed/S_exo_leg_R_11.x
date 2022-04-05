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
 177;
 -13.11842;-21.22654;6.73894;,
 -17.02320;-22.55813;4.89637;,
 -19.05838;-33.53899;5.93269;,
 -15.95497;-36.53134;7.77527;,
 -15.95497;-36.53134;7.77527;,
 -19.05838;-33.53899;5.93269;,
 -19.05838;-33.53899;-6.68267;,
 -15.95499;-36.53133;-8.68944;,
 -15.95499;-36.53133;-8.68944;,
 -19.05838;-33.53899;-6.68267;,
 -17.02320;-22.55813;-4.95230;,
 -13.11844;-21.22654;-6.95907;,
 -13.11844;-21.22654;-6.95907;,
 -17.02320;-22.55813;-4.95230;,
 -17.02320;-22.55813;4.89637;,
 -13.11842;-21.22654;6.73894;,
 -13.11842;-21.22654;6.73894;,
 -15.95497;-36.53134;7.77527;,
 -17.02320;-22.55813;4.89637;,
 -19.05838;-33.53899;5.93269;,
 -18.10794;-28.26472;5.22397;,
 -17.10887;-22.87425;-0.25831;,
 -18.10794;-28.26472;-5.74061;,
 -19.10700;-33.65521;-0.25831;,
 -14.76672;-5.68176;-4.61259;,
 -13.02242;-0.57353;-4.61259;,
 -3.64460;-19.56084;-4.45501;,
 -5.03723;-21.34677;-4.45501;,
 -5.03723;-21.34677;4.60210;,
 -3.64460;-19.56084;4.60210;,
 -12.60689;-0.57349;4.68130;,
 -14.35117;-5.68178;4.68130;,
 -13.02242;-0.57353;-4.61259;,
 -12.60689;-0.57349;4.68130;,
 -3.64460;-19.56084;4.60210;,
 -3.64460;-19.56084;-4.45501;,
 -14.52609;-5.75427;0.74744;,
 -14.57082;-5.75428;-0.63301;,
 -5.11199;-21.31914;-0.63301;,
 -5.11199;-21.31914;0.74744;,
 -14.19665;-5.34671;4.70942;,
 -14.62033;-5.43722;-4.59197;,
 -4.86366;-21.08222;-4.43381;,
 -4.76982;-20.93512;4.57537;,
 -14.52609;-5.63734;-2.95835;,
 -14.58801;-5.50742;-4.32363;,
 -4.92888;-20.91876;-2.02300;,
 -5.11196;-21.13164;-0.65771;,
 -14.53374;-6.13148;4.33638;,
 -14.57849;-5.97793;2.97485;,
 -5.11196;-21.09848;0.83213;,
 -5.11196;-21.32633;2.19365;,
 -12.17235;-10.11332;4.24612;,
 -11.96496;-10.11331;-4.02638;,
 -10.90315;-12.05871;-4.02638;,
 -10.90315;-12.05871;4.24612;,
 -10.49846;2.02824;-4.71405;,
 -10.09143;2.49855;-4.82086;,
 -2.98865;-16.17550;-3.57773;,
 -3.71777;-19.73617;-3.47755;,
 -10.46721;2.03171;4.91536;,
 -3.71777;-19.73617;4.01812;,
 -3.13987;-16.37340;4.08594;,
 -10.14573;2.70080;5.04465;,
 -10.06072;2.46117;-4.70673;,
 -10.48930;2.03256;-4.70673;,
 -10.48930;2.03256;4.93560;,
 -10.06072;2.46117;4.93560;,
 -7.16289;4.72264;-2.99802;,
 -0.43012;3.95554;-2.99802;,
 -1.19720;-2.77722;-4.05044;,
 -7.93000;-2.01008;-4.05044;,
 -7.93000;-2.01008;3.93823;,
 -1.19720;-2.77722;3.93823;,
 -0.43012;3.95554;2.83482;,
 -7.16289;4.72264;2.83482;,
 -7.16289;4.72264;2.83482;,
 -0.43012;3.95554;2.83482;,
 0.85286;3.82660;-0.05614;,
 -7.38410;4.85617;-0.05614;,
 -0.43012;3.95554;-2.99802;,
 -7.16289;4.72264;-2.99802;,
 -7.38410;4.85617;-0.05614;,
 -8.99848;-3.03067;-0.05614;,
 -7.93000;-2.01008;3.93823;,
 -7.16289;4.72264;-2.99802;,
 -7.93000;-2.01008;-4.05044;,
 -7.83721;-2.13141;-4.06460;,
 -1.13594;-2.78658;-4.05907;,
 -3.56570;-19.67896;-3.41157;,
 -8.72456;-11.04448;-3.41157;,
 -8.72456;-11.04448;-3.41157;,
 -3.56570;-19.67896;-3.41157;,
 -3.56570;-19.67896;3.96438;,
 -8.72456;-11.04448;3.96438;,
 -8.72456;-11.04448;3.96438;,
 -3.56570;-19.67896;3.96438;,
 -0.92372;-2.85433;3.96438;,
 -8.29968;-2.19919;3.96438;,
 -1.13594;-2.78658;-4.05907;,
 -0.92372;-2.85433;3.96438;,
 -3.56570;-19.67896;-3.41157;,
 -13.62177;-16.84148;-4.05006;,
 -11.53855;-16.84148;-4.05006;,
 -9.47353;-32.55542;-2.82889;,
 -14.16359;-32.27531;-2.82889;,
 -14.16359;-32.27531;-2.82889;,
 -9.47353;-32.55542;-2.82889;,
 -9.47353;-32.55542;3.01648;,
 -14.16359;-32.27531;3.01648;,
 -14.16359;-32.27531;3.01648;,
 -9.47353;-32.55542;3.01648;,
 -11.53855;-16.84148;4.23765;,
 -13.62177;-16.84148;4.23765;,
 -13.62177;-16.84148;4.23765;,
 -13.62177;-16.84148;-4.05006;,
 -14.16359;-32.27531;-2.82889;,
 -13.56579;-16.85910;-4.05006;,
 -8.29968;-16.17063;-4.05006;,
 -4.97430;-21.38960;-4.11255;,
 -11.03806;-21.29657;-3.69427;,
 -11.03806;-21.29657;3.88186;,
 -4.97430;-21.38960;4.30012;,
 -8.29968;-16.17063;4.23765;,
 -13.56579;-16.85910;4.23765;,
 -13.56579;-16.85910;4.23765;,
 -8.29968;-16.17063;4.23765;,
 -8.29968;-16.17063;-4.05006;,
 -13.56579;-16.85910;-4.05006;,
 -5.36318;-4.31593;5.71851;,
 -12.10208;3.94051;5.71851;,
 -16.84346;-10.51763;5.67373;,
 -3.64627;-16.84917;5.71850;,
 -12.10208;3.94051;5.71851;,
 -12.10208;3.94051;-5.11088;,
 -16.84346;-10.51763;-5.15566;,
 -16.84346;-10.51763;5.67373;,
 -12.10208;3.94051;-5.11088;,
 -5.36318;-4.31593;-5.11088;,
 -3.64627;-16.84917;-5.11088;,
 -16.84346;-10.51763;-5.15566;,
 -12.06029;3.92696;-5.11088;,
 -12.06029;3.92696;5.71851;,
 -16.80972;-10.69028;5.71851;,
 -16.80972;-10.69028;-5.11088;,
 -5.36318;-4.31593;-5.03823;,
 -12.10208;3.94051;-5.03823;,
 -16.84346;-10.51763;-5.08300;,
 -3.64627;-16.84917;-5.03823;,
 -12.10208;3.94051;5.61965;,
 -5.36318;-4.31593;5.61965;,
 -3.64627;-16.84917;5.61965;,
 -16.84346;-10.51763;5.57488;,
 -16.24673;-13.54288;-5.24124;,
 -3.68514;-16.82459;-5.24124;,
 -3.68514;-20.51207;-5.24124;,
 -16.24673;-17.23034;-5.24124;,
 -3.68514;-16.82459;5.75142;,
 -16.24673;-13.54288;5.75142;,
 -16.24673;-17.23034;5.75142;,
 -3.68514;-20.51207;5.75142;,
 -3.68514;-16.82459;-5.12545;,
 -16.24673;-13.54288;-5.12545;,
 -16.24673;-17.23034;-5.12545;,
 -3.68514;-20.51207;-5.12545;,
 -16.24673;-13.54288;5.75625;,
 -3.68514;-16.82459;5.75625;,
 -3.68514;-20.51207;5.75625;,
 -16.24673;-17.23034;5.75625;,
 -16.30325;-13.50968;-5.21873;,
 -16.30325;-17.21568;-5.21873;,
 -16.30325;-17.21568;5.82887;,
 -16.30325;-13.50968;5.82887;,
 -16.30325;-17.21568;-5.21873;,
 -16.30325;-13.50968;-5.21873;,
 -16.30325;-13.50968;5.82887;,
 -16.30325;-17.21568;5.82887;;
 
 47;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,16,17,7;,
 4;18,13,6,19;,
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
 4;79,78,80,81;,
 4;76,82,83,84;,
 4;82,85,86,83;,
 4;87,88,89,90;,
 4;91,92,93,94;,
 4;95,96,97,98;,
 4;99,100,93,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,109;,
 4;117,118,119,120;,
 4;121,122,123,124;,
 4;125,126,127,128;,
 4;129,130,131,132;,
 4;133,134,135,136;,
 4;137,138,139,140;,
 4;141,142,143,144;,
 4;145,146,147,148;,
 4;149,150,151,152;,
 4;153,154,155,156;,
 4;157,158,159,160;,
 4;161,162,163,164;,
 4;165,166,167,168;,
 4;169,170,171,172;,
 4;173,174,175,176;;
 
 MeshMaterialList {
  5;
  47;
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  4,
  2,
  4,
  4,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  1,
  1;;
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
  47;
  -0.436499;0.152520;0.886683;,
  -0.694109;-0.719870;0.000000;,
  -0.952279;-0.305228;0.000000;,
  -0.457588;0.201313;-0.866075;,
  -0.983255;0.182235;-0.000000;,
  -0.322765;0.946479;0.000000;,
  0.983255;-0.182234;-0.000001;,
  -0.983255;0.182235;0.000000;,
  0.008557;-0.004496;-0.999953;,
  0.004403;-0.002310;0.999988;,
  -0.855038;-0.518381;0.013844;,
  -0.851799;-0.522976;0.030566;,
  -0.839458;-0.533526;-0.103253;,
  -0.850976;-0.521882;-0.058987;,
  -0.858258;-0.513111;-0.010505;,
  -0.035954;-0.077029;-0.996380;,
  -0.061221;-0.069245;0.995719;,
  -0.707132;0.707082;0.000000;,
  0.017374;0.152484;-0.988153;,
  -0.986619;0.163042;0.000357;,
  0.018194;0.159684;0.987001;,
  0.118620;0.992940;0.000208;,
  -0.028951;-0.051668;-0.998245;,
  -0.858449;-0.512899;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.002332;-0.078483;-0.996913;,
  -0.059619;-0.998221;0.000000;,
  -0.002332;-0.078482;0.996913;,
  -0.029802;-0.053361;-0.998130;,
  -0.029800;-0.053360;0.998131;,
  -0.003169;-0.001354;0.999994;,
  -0.950210;0.311610;0.000000;,
  0.003169;0.001353;-0.999994;,
  0.951057;-0.309017;-0.000000;,
  -0.003169;-0.001353;0.999994;,
  0.003169;0.001353;-0.999994;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.900384;0.434634;-0.020036;,
  0.118586;0.992654;0.023996;,
  0.118587;0.992664;-0.023581;,
  -0.976264;0.161544;0.144267;,
  -0.976434;0.161145;-0.143560;,
  0.988704;-0.149255;-0.013690;,
  -0.999384;0.035084;0.000000;,
  -0.129634;0.991562;0.000000;;
  47;
  4;0,0,0,0;,
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,2,2;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;39,39,39,39;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;20,20,20,20;,
  4;40,40,21,21;,
  4;21,21,41,41;,
  4;42,19,19,42;,
  4;19,43,43,19;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;44,44,44,44;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;45,45,45,45;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;46,46,46,46;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;;
 }
 MeshTextureCoords {
  177;
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
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
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
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
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
  0.500000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
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
