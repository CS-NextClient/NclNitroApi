/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#pragma once

//  interpolation class
class CInterpolation
{
public:
    CInterpolation();
    virtual ~CInterpolation();

    void SetWaypoints(vec3_t *prev, vec3_t start, vec3_t end, vec3_t *next);
    void SetViewAngles(vec3_t start, vec3_t end);
    void SetFOVs(float start, float end);
    void SetSmoothing(bool start, bool end);

    // get interpolated point 0 =< t =< 1, 0 = start, 1 = end
    void Interpolate(float t, vec3_t &point, vec3_t &angle, float *fov);

protected:
    void BezierInterpolatePoint(float t, vec3_t &point);
    void InterpolateAngle(float t, vec3_t &angle);

    vec3_t m_StartPoint;
    vec3_t m_EndPoint;
    vec3_t m_StartAngle;
    vec3_t m_EndAngle;
    vec3_t m_Center;

    float m_StartFov;
    float m_EndFov;

    bool m_SmoothStart;
    bool m_SmoothEnd;
};