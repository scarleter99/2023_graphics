#include "Camera.h"

// TODO: fill up the following function properly
void Camera::set_rotation(const glm::quat& _q)
{
    glm::mat3 mat_q = glm::mat3_cast(_q);
    front_dir_ = mat_q[2];
    right_dir_ = mat_q[0];
    up_dir_ = mat_q[1];
}

// TODO: re-write the following function properly
const glm::quat Camera::get_rotation() const
{
    glm::mat3 m = glm::mat3 (right_dir_, up_dir_, front_dir_);
    return glm::quat_cast(m);
}

// TODO: fill up the following function properly
void Camera::set_pose(const glm::quat& _q, const glm::vec3& _t)
{
    glm::mat3 mat_q = glm::mat3_cast(_q);
    front_dir_ = -mat_q[2];
    right_dir_ = mat_q[0];
    up_dir_ = mat_q[1];
    position_ = _t;
}

// TODO: fill up the following function properly 
void Camera::get_pose(glm::quat& _q, glm::vec3& _t) const
{
    glm::mat3 rotation = glm::mat3 (right_dir_, up_dir_, -front_dir_);
    _q = glm::quat_cast(rotation);
    _t = position_;
}

// TODO: rewrite the following function properly
const glm::mat4 Camera::get_pose() const
{
  return glm::lookAt(position_, position_ + front_dir_, up_dir_);
}

// TODO: fill up the following function properly
void Camera::set_pose(const glm::mat4& _frame)
{
  // +x_cam: right direction of the camera    (it should be a unit vector whose length is 1)
  // right_dir_ = ..... ; // +x
  // +y_cam: up direction of the camera       (it should be a unit vector whose length is 1)
  // up_dir_    = ..... ;    // +y
  // -z_cam: front direction of the camera    (it should be a unit vector whose length is 1)
  // front_dir_ = ..... ;    // -z
  // pos_cam: position of the camera
  // position_  = ..... ;    // pos
    front_dir_ = _frame[2];
    right_dir_ = _frame[0];
    up_dir_ = _frame[1];
    position_ = _frame[3];


}

// TODO: fill up the following function properly
void Camera::set_pose(const glm::vec3& _pos, const glm::vec3& _at, const glm::vec3& _up_dir)
{
  // front_dir_ = ..... ;    // -z_cam direction
  // right_dir_ = ..... ;    // +x_cam direction
  // up_dir_    = ..... ;    // +y_cam direction

  // position_  = ..... ;      // pos
  front_dir_ = glm::normalize(_pos - _at);
  right_dir_ = glm::normalize(glm::cross(_up_dir, front_dir_));
  up_dir_ = glm::cross(front_dir_, right_dir_);
  position_ = _pos;
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt(position_, position_ + front_dir_, up_dir_);
}

// TODO: rewrite the following function properly
const glm::mat4 Camera::get_projection_matrix() const
{
    // TODO: Considering the followings,
    //       You must return a proper projection matrix
    //       i) camera mode: it can be either kOrtho or kPerspective
    //       ii) zoom-in/-out: if the camera mode is kOrtho,
    //                         utilize ortho_scale_ for zoom-in/-out
    //                         if the camera mode is kPerspective,
    //                         utilize fovy_ for zoom-in/-out
    //       iii) aspect ratio: utilize aspect_ in the both camera modes
    //       iv) near/far clipping planes: utilize near_, far_
    if (mode_ == kOrtho)
        return glm::ortho(-ortho_scale_ * aspect_, ortho_scale_ * aspect_, -ortho_scale_, ortho_scale_,
                          near_, far_);
    else
        return glm::perspective(glm::radians(fovy_), aspect_, near_, far_);
}

// TODO: fill up the following functions properly 
void Camera::move_forward(float delta)
{
    position_ += delta * front_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_backward(float delta)
{
    position_ -= delta * front_dir_;
}
using namespace std;
// TODO: fill up the following functions properly
void Camera::move_left(float delta)
{
    position_ -= delta * right_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_right(float delta)
{
    position_ += delta * right_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_up(float delta)
{
    position_ += delta * up_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_down(float delta)
{
    position_ -= delta * up_dir_;
}
