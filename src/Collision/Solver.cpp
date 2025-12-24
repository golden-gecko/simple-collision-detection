#include "PCH.hpp"

#include "Collision/Solver.hpp"

namespace Collision
{
    bool Solver::collide(const AABB& s1, const AABB& s2)
    {
        return Ogre::Math::Abs(s1.getPosition().x - s2.getPosition().x) < s1.getSize().x + s2.getSize().x
            && Ogre::Math::Abs(s1.getPosition().y - s2.getPosition().y) < s1.getSize().y + s2.getSize().y
            && Ogre::Math::Abs(s1.getPosition().z - s2.getPosition().z) < s1.getSize().z + s2.getSize().z;
    }

    bool Solver::collide(const AABB& s1, const Plane& s2)
    {
        float r = s1.getSize().x * Ogre::Math::Abs(s2.getNormal().dotProduct(s1.getAxes()[0]))
                + s1.getSize().y * Ogre::Math::Abs(s2.getNormal().dotProduct(s1.getAxes()[1]))
                + s1.getSize().z * Ogre::Math::Abs(s2.getNormal().dotProduct(s1.getAxes()[2]));

        float s = s2.getNormal().dotProduct(s1.getPosition()) - s2.getDistance();
        
        return Ogre::Math::Abs(s) <= r;
    }

    bool Solver::collide(const AABB& s1, const Sphere& s2)
    {
        return Ogre::Math::Abs(s1.getPosition().x - s2.getRadius()) < s1.getSize().x + s2.getRadius()
            && Ogre::Math::Abs(s1.getPosition().y - s2.getRadius()) < s1.getSize().y + s2.getRadius()
            && Ogre::Math::Abs(s1.getPosition().z - s2.getRadius()) < s1.getSize().z + s2.getRadius();
    }

    bool Solver::collide(const Sphere& s1, const AABB& s2)
    {
        return collide(s2, s1);
    }

    bool Solver::collide(const Sphere& s1, const Plane& s2)
    {
        return Ogre::Math::Abs(s1.getPosition().dotProduct(s2.getNormal()) - s2.getDistance()) <= s1.getRadius();
    }

    bool Solver::collide(const Sphere& s1, const Sphere& s2)
    {
        return s1.getPosition().distance(s2.getPosition()) <= s1.getRadius() + s2.getRadius();
    }

    bool Solver::collide(const Plane& s1, const AABB& s2)
    {
        return collide(s2, s1);
    }

    bool Solver::collide(const Plane& s1, const Plane& s2)
    {
        return false;
    }

    bool Solver::collide(const Plane& s1, const Sphere& s2)
    {
        return collide(s2, s1);
    }

    bool Solver::collide(const OBB& s1, const OBB& s2)
    {
        const OBB& a = s1;
        const OBB& b = s2;

        float ra, rb;
        float R[3][3], AbsR[3][3];

        const float EPSILON = 0.01f;

        // From book "Real-Time Collision Detection" by Christer Ericson.
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                R[i][j] = a.u[i].dotProduct(b.u[j]);
            }
        }

        // Compute translation vector t
        Ogre::Vector3f t = b.getPosition() - a.getPosition();

        // Bring translation into a's coordinate frame
        t = Ogre::Vector3f(t.dotProduct(a.u[0]), t.dotProduct(a.u[2]), t.dotProduct(a.u[2]));

        // Compute common subexpressions. Add in an epsilon term to
        // counteract arithmetic errors when two edges are parallel and
        // their cross product is (near) null (see text for details)
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                AbsR[i][j] = Ogre::Math::Abs(R[i][j]) + EPSILON;
            }
        }

        // Test axes L = A0, L = A1, L = A2
        for (int i = 0; i < 3; i++)
        {
            ra = a.e[i];
            rb = b.e[0] * AbsR[i][0] + b.e[1] * AbsR[i][1] + b.e[2] * AbsR[i][2];

            if (Ogre::Math::Abs(t[i]) > ra + rb)
            {
                return false;
            }
        }

        // Test axes L = B0, L = B1, L = B2
        for (int i = 0; i < 3; i++)
        {
            ra = a.e[0] * AbsR[0][i] + a.e[1] * AbsR[1][i] + a.e[2] * AbsR[2][i];
            rb = b.e[i];

            if (Ogre::Math::Abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb)
            {
                return false;
            }
        }

        // Test axis L = A0 x B0
        ra = a.e[1] * AbsR[2][0] + a.e[2] * AbsR[1][0];
        rb = b.e[1] * AbsR[0][2] + b.e[2] * AbsR[0][1];
        if (Ogre::Math::Abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return false;

        // Test axis L = A0 x B1
        ra = a.e[1] * AbsR[2][1] + a.e[2] * AbsR[1][1];
        rb = b.e[0] * AbsR[0][2] + b.e[2] * AbsR[0][0];
        if (Ogre::Math::Abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return false;

        // Test axis L = A0 x B2
        ra = a.e[1] * AbsR[2][2] + a.e[2] * AbsR[1][2];
        rb = b.e[0] * AbsR[0][1] + b.e[1] * AbsR[0][0];
        if (Ogre::Math::Abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return false;

        // Test axis L = A1 x B0
        ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0];
        rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
        if (Ogre::Math::Abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return false;

        // Test axis L = A1 x B1
        ra = a.e[0] * AbsR[2][1] + a.e[2] * AbsR[0][1];
        rb = b.e[0] * AbsR[1][2] + b.e[2] * AbsR[1][0];
        if (Ogre::Math::Abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return false;

        // Test axis L = A1 x B2
        ra = a.e[0] * AbsR[2][2] + a.e[2] * AbsR[0][2];
        rb = b.e[0] * AbsR[1][1] + b.e[1] * AbsR[1][0];
        if (Ogre::Math::Abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return false;

        // Test axis L = A2 x B0
        ra = a.e[0] * AbsR[1][0] + a.e[1] * AbsR[0][0];
        rb = b.e[1] * AbsR[2][2] + b.e[2] * AbsR[2][1];
        if (Ogre::Math::Abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return false;

        // Test axis L = A2 x B1
        ra = a.e[0] * AbsR[1][1] + a.e[1] * AbsR[0][1];
        rb = b.e[0] * AbsR[2][2] + b.e[2] * AbsR[2][0];
        if (Ogre::Math::Abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return false;

        // Test axis L = A2 x B2
        ra = a.e[0] * AbsR[1][2] + a.e[1] * AbsR[0][2];
        rb = b.e[0] * AbsR[2][1] + b.e[1] * AbsR[2][0];
        if (Ogre::Math::Abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return false;

        // Since no separating axis is found, the OBBs must be intersecting
        return true;
    }

    bool Solver::collide(const OBB& s1, const Plane& s2)
    {
        return false;
    }

    bool Solver::collide(const OBB& s1, const Sphere& s2)
    {
        return false;
    }
}
