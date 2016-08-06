#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
const int column_no=20;
const int height_diff=3;

const float column_velocity=5;
const float sky_velocity=0.5;
const float city_velocity=0.8;
const float jungle_velocity=2;

Image World::column_image;
Image World::ground_image;
Image World::ground_2d_image;
Image World::empty_image;
#endif // WORLD_H_INCLUDED
