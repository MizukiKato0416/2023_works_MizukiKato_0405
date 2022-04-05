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
 -2.71885;-0.94755;-3.85376;,
 -1.03689;-0.94755;-4.56884;,
 -0.91564;-7.00026;-4.56884;,
 -2.50781;-7.00026;-3.85376;,
 1.23793;-0.94755;-4.56884;,
 1.23774;-7.00026;-4.56884;,
 2.91350;-0.94755;-3.73604;,
 2.82386;-7.00026;-3.73604;,
 -0.73686;-12.95095;-4.26145;,
 -2.25915;-12.95095;-3.54637;,
 1.32199;-12.95095;-4.26145;,
 2.83848;-12.95095;-3.42865;,
 -0.54073;-18.59326;-3.70204;,
 -1.96744;-18.59326;-2.98696;,
 1.38887;-18.59326;-3.70204;,
 2.81016;-18.59326;-2.86924;,
 2.91350;-0.94755;-3.73604;,
 3.51275;-0.94755;-1.86534;,
 3.39112;-7.00026;-1.86534;,
 2.82386;-7.00026;-3.73604;,
 3.51275;-0.94755;0.83816;,
 3.39112;-7.00026;0.83816;,
 3.01112;-0.94755;3.20634;,
 2.91627;-7.00026;2.68073;,
 3.38085;-12.95095;-1.86534;,
 2.83848;-12.95095;-3.42865;,
 3.38085;-12.95095;0.46854;,
 2.92684;-12.95095;1.88231;,
 3.31847;-18.59326;-1.30593;,
 2.81016;-18.59326;-2.86924;,
 3.31847;-18.59326;0.09980;,
 2.89297;-18.59326;1.51357;,
 3.01112;-0.94755;3.20634;,
 1.23793;-0.94755;4.06726;,
 1.23774;-7.00026;3.54166;,
 2.91627;-7.00026;2.68073;,
 -1.03689;-0.94755;4.06726;,
 -0.91564;-7.00026;3.54166;,
 -2.68346;-0.94755;3.50575;,
 -2.47431;-7.00026;2.98014;,
 1.32199;-12.95095;2.74324;,
 2.92684;-12.95095;1.88231;,
 -0.73686;-12.95095;2.74324;,
 -2.22712;-12.95095;2.18172;,
 1.38887;-18.59326;2.37450;,
 2.89297;-18.59326;1.51357;,
 -0.54073;-18.59326;2.37450;,
 -1.93742;-18.59326;1.81299;,
 -2.68346;-0.94755;3.50575;,
 -3.31171;-0.94755;0.83816;,
 -3.06902;-7.00026;0.83816;,
 -2.47431;-7.00026;2.98014;,
 -3.31171;-0.94755;-1.86534;,
 -3.06902;-7.00026;-1.86534;,
 -2.71885;-0.94755;-3.85376;,
 -2.50781;-7.00026;-3.85376;,
 -2.79572;-12.95095;0.46854;,
 -2.22712;-12.95095;2.18172;,
 -2.79572;-12.95095;-1.86534;,
 -2.25915;-12.95095;-3.54637;,
 -2.47032;-18.59326;0.09980;,
 -1.93742;-18.59326;1.81299;,
 -2.47032;-18.59326;-1.30593;,
 -1.96744;-18.59326;-2.98696;,
 -1.03689;-0.94755;4.06726;,
 -1.32309;0.94660;1.47656;,
 -3.31171;-0.94755;0.83816;,
 1.23793;-0.94755;4.06726;,
 1.52413;0.94660;1.47656;,
 3.51275;-0.94755;0.83816;,
 -1.32309;0.94660;-1.90720;,
 -3.31171;-0.94755;-1.86534;,
 1.52413;0.94660;-1.90720;,
 3.51275;-0.94755;-1.86534;,
 -1.03689;-0.94755;-4.56884;,
 -2.71885;-0.94755;-3.85376;,
 1.23793;-0.94755;-4.56884;,
 2.91350;-0.94755;-3.73604;,
 -2.47032;-18.59326;0.09980;,
 -0.54073;-20.22534;0.09980;,
 -0.54073;-18.59326;2.37450;,
 1.38887;-20.27087;0.09980;,
 1.38887;-18.59326;2.37450;,
 3.31847;-18.59326;0.09980;,
 -2.47032;-18.59326;-1.30593;,
 -0.54073;-20.22534;-1.30593;,
 1.38887;-20.22534;-1.30593;,
 3.31847;-18.59326;-1.30593;,
 -1.96744;-18.59326;-2.98696;,
 -0.54073;-18.59326;-3.70204;,
 1.38887;-18.59326;-3.70204;,
 2.81016;-18.59326;-2.86924;;
 
 54;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;19,18,24,25;,
 4;18,21,26,24;,
 4;21,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;35,34,40,41;,
 4;34,37,42,40;,
 4;37,39,43,42;,
 4;41,40,44,45;,
 4;40,42,46,44;,
 4;42,43,47,46;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;51,50,56,57;,
 4;50,53,58,56;,
 4;53,55,59,58;,
 4;57,56,60,61;,
 4;56,58,62,60;,
 4;58,59,63,62;,
 4;48,64,65,66;,
 4;64,67,68,65;,
 4;67,22,69,68;,
 4;66,65,70,71;,
 4;65,68,72,70;,
 4;68,69,73,72;,
 4;71,70,74,75;,
 4;70,72,76,74;,
 4;72,73,77,76;,
 4;78,79,80,61;,
 4;79,81,82,80;,
 4;81,83,31,82;,
 4;84,85,79,78;,
 4;85,86,81,79;,
 4;86,87,83,81;,
 4;88,89,85,84;,
 4;89,90,86,85;,
 4;90,91,87,86;;
 
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
  -0.723075;0.285686;-0.628925;,
  -0.150968;0.303021;-0.940950;,
  0.279027;0.460446;-0.842694;,
  -0.752204;-0.043372;-0.657501;,
  -0.208972;-0.031783;-0.977405;,
  0.238916;-0.024847;-0.970722;,
  -0.754271;-0.081870;-0.651439;,
  -0.218010;-0.081886;-0.972505;,
  0.249031;-0.071313;-0.965866;,
  -0.707559;-0.376765;-0.597836;,
  -0.258523;-0.524743;-0.811055;,
  0.281547;-0.517544;-0.808010;,
  0.734519;0.285921;-0.615411;,
  0.889556;0.410451;-0.200552;,
  0.897423;0.405706;0.173305;,
  0.765923;-0.018567;-0.642664;,
  0.988084;-0.011539;-0.153480;,
  0.991650;-0.018759;0.127583;,
  0.768902;-0.046265;-0.637691;,
  0.987188;-0.014965;-0.158860;,
  0.989261;-0.016812;0.145191;,
  0.728306;-0.344614;-0.592294;,
  0.870016;-0.450404;-0.200520;,
  0.875717;-0.443736;0.190309;,
  0.763035;0.257401;0.592893;,
  0.228618;-0.086041;0.969707;,
  -0.167100;-0.089851;0.981837;,
  0.778337;-0.067965;0.624157;,
  0.233138;-0.106692;0.966573;,
  -0.170552;-0.113487;0.978792;,
  0.774225;-0.060608;0.630001;,
  0.243880;-0.095009;0.965140;,
  -0.179065;-0.104603;0.978261;,
  0.736152;-0.326216;0.593012;,
  0.281078;-0.492673;0.823571;,
  -0.234343;-0.500816;0.833227;,
  -0.720058;0.259428;0.643594;,
  -0.968365;0.232562;0.090466;,
  -0.892777;0.405740;-0.195766;,
  -0.729452;-0.096485;0.677193;,
  -0.989404;-0.050826;0.135999;,
  -0.988783;-0.043159;-0.142986;,
  -0.724694;-0.098451;0.682002;,
  -0.986641;-0.061851;0.150708;,
  -0.987357;-0.059066;-0.147099;,
  -0.681791;-0.367643;0.632455;,
  -0.856421;-0.476841;0.197900;,
  -0.858672;-0.476630;-0.188432;,
  -0.321287;0.907037;0.272137;,
  0.332333;0.904233;0.268174;,
  -0.321057;0.907588;-0.270569;,
  0.326002;0.905476;-0.271729;,
  -0.302821;-0.915942;0.263343;,
  0.308651;-0.914965;0.259949;,
  -0.304522;-0.916631;-0.258950;,
  0.305189;-0.915073;-0.263629;,
  -0.249779;0.820617;0.514003;,
  -0.482479;0.777872;0.402652;,
  0.271132;0.817139;0.508696;,
  -0.482558;0.774979;-0.408100;;
  54;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,12,15,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,15,18,8;,
  4;6,7,10,9;,
  4;7,8,11,10;,
  4;8,18,21,11;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;14,24,27,17;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;17,27,30,20;,
  4;18,19,22,21;,
  4;19,20,23,22;,
  4;20,30,33,23;,
  4;24,25,28,27;,
  4;25,26,29,28;,
  4;26,36,39,29;,
  4;27,28,31,30;,
  4;28,29,32,31;,
  4;29,39,42,32;,
  4;30,31,34,33;,
  4;31,32,35,34;,
  4;32,42,45,35;,
  4;36,37,40,39;,
  4;37,38,41,40;,
  4;38,0,3,41;,
  4;39,40,43,42;,
  4;40,41,44,43;,
  4;41,3,6,44;,
  4;42,43,46,45;,
  4;43,44,47,46;,
  4;44,6,9,47;,
  4;36,56,48,57;,
  4;56,58,49,48;,
  4;58,24,14,49;,
  4;37,48,50,38;,
  4;48,49,51,50;,
  4;49,14,13,51;,
  4;38,50,59,0;,
  4;50,51,2,1;,
  4;51,13,12,2;,
  4;46,52,35,45;,
  4;52,53,34,35;,
  4;53,23,33,34;,
  4;47,54,52,46;,
  4;54,55,53,52;,
  4;55,22,23,53;,
  4;9,10,54,47;,
  4;10,11,55,54;,
  4;11,21,22,55;;
 }
 MeshTextureCoords {
  92;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
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