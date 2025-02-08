#pragma once

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
        int animation = 0;
        int frame = 0;

        bool isSame(LastAnimation lastAnim) {
            if(this->animation == lastAnim.animation /*&& this->frame == frame*/) 
                return true;

            this->animation = lastAnim.animation;
            this->frame = lastAnim.frame;
            
            return false;
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