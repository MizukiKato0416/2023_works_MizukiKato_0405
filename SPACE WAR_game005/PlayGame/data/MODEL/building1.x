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
 48;
 -33.69117;84.07866;-39.81051;,
 -44.54672;72.13245;-52.63779;,
 -55.05446;72.13245;-42.26603;,
 -41.63829;84.07866;-31.96625;,
 -13.16395;84.07866;-39.81051;,
 -17.40547;72.13245;-52.63779;,
 -5.94832;84.07866;-31.96625;,
 -7.86493;72.13245;-42.26603;,
 5.94832;84.07866;-31.96625;,
 7.86493;72.13245;-42.26603;,
 13.16395;84.07866;-39.81051;,
 17.40547;72.13245;-52.63779;,
 33.69117;84.07866;-39.81051;,
 44.54672;72.13245;-52.63779;,
 41.63829;84.07866;-31.96625;,
 55.05446;72.13245;-42.26603;,
 -44.54672;-0.45343;-52.63779;,
 -55.05446;-0.45343;-42.26603;,
 -17.40547;-0.45343;-52.63779;,
 -7.86493;-0.45343;-42.26603;,
 7.86493;-0.45343;-42.26603;,
 17.40547;-0.45343;-52.63779;,
 44.54672;-0.45343;-52.63779;,
 55.05446;-0.45343;-42.26603;,
 41.63829;84.07866;31.96625;,
 55.05446;72.13245;42.26603;,
 55.05446;-0.45343;42.26603;,
 33.69117;84.07866;39.81051;,
 44.54672;72.13245;52.63779;,
 13.16395;84.07866;39.81051;,
 17.40547;72.13245;52.63779;,
 5.94832;84.07866;31.96625;,
 7.86493;72.13245;42.26603;,
 -5.94832;84.07866;31.96625;,
 -7.86493;72.13245;42.26603;,
 -13.16395;84.07866;39.81051;,
 -17.40547;72.13245;52.63779;,
 -33.69117;84.07866;39.81051;,
 -44.54672;72.13245;52.63779;,
 -41.63829;84.07866;31.96625;,
 -55.05446;72.13245;42.26603;,
 44.54672;-0.45343;52.63779;,
 17.40547;-0.45343;52.63779;,
 7.86493;-0.45343;42.26603;,
 -7.86493;-0.45343;42.26603;,
 -17.40547;-0.45343;52.63779;,
 -44.54672;-0.45343;52.63779;,
 -55.05446;-0.45343;42.26603;;
 
 92;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,1;,
 3;4,1,0;,
 3;6,7,5;,
 3;6,5,4;,
 3;8,9,7;,
 3;8,7,6;,
 3;10,11,9;,
 3;10,9,8;,
 3;12,13,11;,
 3;12,11,10;,
 3;14,15,13;,
 3;14,13,12;,
 3;1,16,17;,
 3;1,17,2;,
 3;5,18,16;,
 3;5,16,1;,
 3;7,19,18;,
 3;7,18,5;,
 3;9,20,19;,
 3;9,19,7;,
 3;11,21,20;,
 3;11,20,9;,
 3;13,22,21;,
 3;13,21,11;,
 3;15,23,22;,
 3;15,22,13;,
 3;24,25,15;,
 3;24,15,14;,
 3;25,26,23;,
 3;25,23,15;,
 3;27,28,25;,
 3;27,25,24;,
 3;29,30,28;,
 3;29,28,27;,
 3;31,32,30;,
 3;31,30,29;,
 3;33,34,32;,
 3;33,32,31;,
 3;35,36,34;,
 3;35,34,33;,
 3;37,38,36;,
 3;37,36,35;,
 3;39,40,38;,
 3;39,38,37;,
 3;28,41,26;,
 3;28,26,25;,
 3;30,42,41;,
 3;30,41,28;,
 3;32,43,42;,
 3;32,42,30;,
 3;34,44,43;,
 3;34,43,32;,
 3;36,45,44;,
 3;36,44,34;,
 3;38,46,45;,
 3;38,45,36;,
 3;40,47,46;,
 3;40,46,38;,
 3;3,2,40;,
 3;3,40,39;,
 3;2,17,47;,
 3;2,47,40;,
 3;37,0,3;,
 3;37,3,39;,
 3;35,4,0;,
 3;35,0,37;,
 3;33,6,4;,
 3;33,4,35;,
 3;31,8,6;,
 3;31,6,33;,
 3;29,10,8;,
 3;29,8,31;,
 3;27,12,10;,
 3;27,10,29;,
 3;24,14,12;,
 3;24,12,27;,
 3;16,46,47;,
 3;16,47,17;,
 3;18,45,46;,
 3;18,46,16;,
 3;19,44,45;,
 3;19,45,18;,
 3;20,43,44;,
 3;20,44,19;,
 3;21,42,43;,
 3;21,43,20;,
 3;22,41,42;,
 3;22,42,21;,
 3;23,26,41;,
 3;23,41,22;;
 
 MeshMaterialList {
  1;
  92;
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
   0.592800;0.592800;0.592800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\building.png";
   }
  }
 }
 MeshNormals {
  49;
  -0.372642;0.923736;-0.088595;,
  -0.144933;0.952473;-0.267935;,
  0.125591;0.919657;-0.372100;,
  0.261976;0.882908;-0.389670;,
  -0.127625;0.904405;-0.407142;,
  -0.259882;0.891199;-0.371786;,
  0.073039;0.945235;-0.318114;,
  -0.828284;0.470321;-0.304539;,
  -0.354759;0.445762;-0.821853;,
  0.392660;0.298897;-0.869758;,
  0.406780;0.328608;-0.852377;,
  -0.389457;0.281635;-0.876929;,
  -0.412543;0.363659;-0.835201;,
  0.299578;0.465757;-0.832661;,
  -0.860570;0.000000;-0.509332;,
  -0.250780;0.000000;-0.968044;,
  0.530185;0.000000;-0.847882;,
  0.265092;0.000000;-0.964223;,
  -0.530185;0.000000;-0.847882;,
  -0.265092;0.000000;-0.964223;,
  0.501559;0.000000;-0.865123;,
  0.391990;0.893580;-0.218766;,
  0.814633;0.453821;-0.361137;,
  0.967029;0.000000;-0.254666;,
  0.372642;0.923736;0.088595;,
  0.144933;0.952473;0.267935;,
  -0.125591;0.919657;0.372100;,
  -0.261976;0.882908;0.389670;,
  0.127625;0.904405;0.407142;,
  0.259882;0.891199;0.371786;,
  -0.073039;0.945235;0.318114;,
  0.828284;0.470321;0.304539;,
  0.354759;0.445762;0.821853;,
  -0.392660;0.298897;0.869758;,
  -0.406780;0.328608;0.852377;,
  0.389457;0.281635;0.876929;,
  0.412543;0.363659;0.835201;,
  -0.299578;0.465757;0.832661;,
  0.860570;0.000000;0.509332;,
  0.250780;0.000000;0.968044;,
  -0.530185;0.000000;0.847882;,
  -0.265092;0.000000;0.964223;,
  0.530185;0.000000;0.847882;,
  0.265092;0.000000;0.964223;,
  -0.501559;0.000000;0.865123;,
  -0.391990;0.893580;0.218766;,
  -0.814633;0.453821;0.361137;,
  -0.967029;0.000000;0.254666;,
  0.000000;-1.000000;-0.000000;;
  92;
  3;1,8,7;,
  3;1,7,0;,
  3;2,9,8;,
  3;2,8,1;,
  3;3,10,9;,
  3;3,9,2;,
  3;4,11,10;,
  3;4,10,3;,
  3;5,12,11;,
  3;5,11,4;,
  3;6,13,12;,
  3;6,12,5;,
  3;21,22,13;,
  3;21,13,6;,
  3;8,15,14;,
  3;8,14,7;,
  3;9,16,15;,
  3;9,15,8;,
  3;10,17,16;,
  3;10,16,9;,
  3;11,18,17;,
  3;11,17,10;,
  3;12,19,18;,
  3;12,18,11;,
  3;13,20,19;,
  3;13,19,12;,
  3;22,23,20;,
  3;22,20,13;,
  3;24,31,22;,
  3;24,22,21;,
  3;31,38,23;,
  3;31,23,22;,
  3;25,32,31;,
  3;25,31,24;,
  3;26,33,32;,
  3;26,32,25;,
  3;27,34,33;,
  3;27,33,26;,
  3;28,35,34;,
  3;28,34,27;,
  3;29,36,35;,
  3;29,35,28;,
  3;30,37,36;,
  3;30,36,29;,
  3;45,46,37;,
  3;45,37,30;,
  3;32,39,38;,
  3;32,38,31;,
  3;33,40,39;,
  3;33,39,32;,
  3;34,41,40;,
  3;34,40,33;,
  3;35,42,41;,
  3;35,41,34;,
  3;36,43,42;,
  3;36,42,35;,
  3;37,44,43;,
  3;37,43,36;,
  3;46,47,44;,
  3;46,44,37;,
  3;0,7,46;,
  3;0,46,45;,
  3;7,14,47;,
  3;7,47,46;,
  3;30,1,0;,
  3;30,0,45;,
  3;29,2,1;,
  3;29,1,30;,
  3;28,3,2;,
  3;28,2,29;,
  3;27,4,3;,
  3;27,3,28;,
  3;26,5,4;,
  3;26,4,27;,
  3;25,6,5;,
  3;25,5,26;,
  3;24,21,6;,
  3;24,6,25;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;;
 }
 MeshTextureCoords {
  48;
  -1.198279;-3.987158;,
  -1.741056;-3.389848;,
  -2.266443;-3.389848;,
  -1.595634;-3.987158;,
  -0.171917;-3.987158;,
  -0.383994;-3.389848;,
  0.188864;-3.987158;,
  0.093034;-3.389848;,
  0.783696;-3.987158;,
  0.879526;-3.389848;,
  1.144477;-3.987158;,
  1.356554;-3.389848;,
  2.170838;-3.987158;,
  2.713616;-3.389848;,
  2.568194;-3.987158;,
  3.239003;-3.389848;,
  -1.741056;0.239446;,
  -2.266443;0.239446;,
  -0.383994;0.239446;,
  0.093034;0.239446;,
  0.879526;0.239446;,
  1.356554;0.239446;,
  2.713616;0.239446;,
  3.239003;0.239446;,
  2.568194;-3.987158;,
  3.239003;-3.389848;,
  3.239003;0.239446;,
  2.170838;-3.987158;,
  2.713616;-3.389848;,
  1.144477;-3.987158;,
  1.356554;-3.389848;,
  0.783696;-3.987158;,
  0.879526;-3.389848;,
  0.188864;-3.987158;,
  0.093034;-3.389848;,
  -0.171917;-3.987158;,
  -0.383994;-3.389848;,
  -1.198279;-3.987158;,
  -1.741056;-3.389848;,
  -1.595634;-3.987158;,
  -2.266443;-3.389848;,
  2.713616;0.239446;,
  1.356554;0.239446;,
  0.879526;0.239446;,
  0.093034;0.239446;,
  -0.383994;0.239446;,
  -1.741056;0.239446;,
  -2.266443;0.239446;;
 }
}
