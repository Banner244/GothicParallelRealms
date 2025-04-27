#pragma once
#include <vector>

namespace DataStructures {
    struct LastPosition {
        float x = 0;
        float z = 0;
        float y = 0;

        float yaw = 0;
        float pitch = 0;
        float roll = 0;

        bool isSame(LastPosition lastPos){
            int zCutted = static_cast<int>(this->z);
            int zNewCutted = static_cast<int>(z);

            if(this->x == lastPos.x && zCutted == zNewCutted && this->y == lastPos.y && this->yaw == lastPos.yaw && this->pitch == lastPos.pitch && this->roll == lastPos.roll ) 
                return true;

            this->x = lastPos.x;
            this->z = lastPos.z;
            this->y = lastPos.y;

            this->yaw = lastPos.yaw;
            this->pitch = lastPos.pitch;
            this->roll = lastPos.roll;

            return false;
        }
    };

    struct LastAnimation {
        int animationCount = 0;
        std::vector<int> animationIds;

        bool isSame(const LastAnimation& lastAnim) {
            if (lastAnim.animationCount != animationCount || lastAnim.animationIds.size() != animationIds.size()) {
                this->animationCount = lastAnim.animationCount;
                this->animationIds = lastAnim.animationIds;
                return false;
            }
        
            for (int i = 0; i < animationCount; i++) {
                if (lastAnim.animationIds[i] != animationIds[i]) {
                    this->animationIds = lastAnim.animationIds;
                    return false;
                }
            }
        
            return true;
        }
    };

    struct LastRotation {
        float yaw = 0;
        float pitch = 0;
        float roll = 0;

        bool isSame(LastRotation lastRot){
            if(this->yaw == lastRot.yaw && this->pitch == lastRot.pitch && this->roll == lastRot.roll) 
                return true;

            this->yaw = lastRot.yaw;
            this->pitch = lastRot.pitch;
            this->roll = lastRot.roll;

            return false;
        }
    };
}