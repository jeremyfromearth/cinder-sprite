#pragma once

// cinder
#include "cinder/Timeline.h"
#include "cinder/Vector.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"

// sfmoma
#include "provider.h"
/////////////////////////////////////////////////
//
//  sprite
//  A graphical element for
//  display of a gl::Texture
//
/////////////////////////////////////////////////
class sprite {
public:
  //////////////////////////////////////////////////////
  // enums
  //////////////////////////////////////////////////////
  enum origin_point {
    TopLeft = 0,
    Center = 1
  };
  
  //////////////////////////////////////////////////////
  // static
  //////////////////////////////////////////////////////
  typedef std::shared_ptr<sprite> sprite_ref;

  static sprite_ref create();

  static sprite_ref create(texture_provider_ref provider_ref);

  static ci::signals::Signal<void()> complete;

  //////////////////////////////////////////////////////
  // ctr(s) / dctr(s)
  //////////////////////////////////////////////////////
  sprite(const texture_provider_ref texture_provider);

  sprite();

  //////////////////////////////////////////////////////
  // properties
  //////////////////////////////////////////////////////
  texture_provider_ref provider;

  //////////////////////////////////////////////////////
  // getters
  //////////////////////////////////////////////////////
  texture_provider_ref get_provider();

  //////////////////////////////////////////////////////
  // setters
  //////////////////////////////////////////////////////
  void set_alpha(float new_alpha);

  void set_coordinates(ci::vec2 new_coords);

  void set_origin(origin_point new_origin);

  void set_provider(texture_provider_ref provider_ref);

  void set_scale(float new_scale);

  void set_tint(ci::Color new_tint);

  void set_zoom(float new_zoom);

  void set_zoom_center(ci::vec2 new_focal_point);

  //////////////////////////////////////////////////////
  // methods
  //////////////////////////////////////////////////////
  // draw the sprite
  void draw();

  // schedule an alpha animation
  ci::TweenRef<float> alpha_to(
    ci::TimelineRef animator,
    float target,
    float duration = 0,
    float delay = 0,
    ci::EaseFn fn = ci::easeInOutQuad);

  // schedule a mask animation to hide the sprite
  void mask_hide(
    ci::TimelineRef animator,
    std::string animation,
    float duration =0 ,
    float delay = 0,
    ci::EaseFn fn = ci::easeInOutQuad);

  // schedule a mask animation to reveal the sprite
  void mask_reveal(
    ci::TimelineRef animator,
    std::string animation,
    float duration = 0,
    float delay = 0,
    ci::EaseFn fn = ci::easeInOutQuad);

  // schedule an animation to move the sprite
  // relative to coords, applied to offset
  ci::TweenRef<ci::vec2> move_to(
    ci::TimelineRef animator,
    ci::vec2 target,
    float duration = 0,
    float delay = 0,
    ci::EaseFn fn = ci::easeInOutQuad);

  // schedule an animation to scale the sprite
  ci::TweenRef<float> scale_to(
    ci::TimelineRef animator,
    float target,
    float duration = 0,
    float delay = 0,
    ci::EaseFn fn = ci::easeInOutQuad);

  // schedule an animation to start media
  void start_media(ci::TimelineRef animator, bool loop, bool cue_complete);

  // schedule an animation to tint the sprite
  ci::TweenRef<ci::Color> tint_to(
    ci::TimelineRef animator,
    ci::Color target,
    float duration = 0,
    float delay = 0,
    ci::EaseFn fn = ci::easeInOutQuad);

  // update the sprite (called every frame)
  void update();

  // schedule an animation to zoom the sprite
  ci::TweenRef<float> zoom_to(
    ci::TimelineRef animator,
    float target,
    float duration = 0,
    float delay = 0,
    ci::EaseFn fn = ci::easeInOutQuad);

private:
  //////////////////////////////////////////////////////
  // properties
  //////////////////////////////////////////////////////
  // texture
  ci::Rectf bounds;           // normalized bounds
  ci::Area zoom_area;         // an area used to zoom into the image
  ci::vec2 coordinates;       // absolute coordinates (center of sprite)
  float scale;                // absolute scale of the sprite
  ci::vec2 texture_size;      // width and height of the texture
  ci::gl::TextureRef texture; // the original texture
  origin_point origin;        // the origin by which to scale and translate this sprite

  // animatables
  ci::Anim<ci::Color> tint;       // the tint to be applied to this sprite
  ci::Anim<float> zoom;           // the level of zooming 0 = none, 1.0 completely zoomed in
  ci::Anim<float> scale_offset;   // offset from absolute scale
  ci::Anim<ci::vec2> offset;      // offset from absolute coords
  ci::Anim<float> alpha;          // alpha channel
  ci::Anim<ci::Rectf> mask_rect;  // rectangular mask

  // cropping and zooming
  ci::gl::FboRef fbo;         // an fbo used in the zoom compositing
  ci::gl::TextureRef crop;    // zoomed and cropped texture
  ci::vec2 zoom_center;       // the center point to zoom into

  //////////////////////////////////////////////////////
  // methods
  //////////////////////////////////////////////////////
  void update_zoom();  // update the zoom area

  void update_fbo();   // update the fbo

  void apply_mask_animation(
    ci::TimelineRef animator,
    ci::Rectf mask_start,
    ci::Rectf mask_target,
    float duration, float delay,
    ci::EaseFn fn = ci::easeInOutQuad);   // generic mask animator, used by mask_reveal and mask_hide
};

//////////////////////////////////////////////////////
// typedefs
//////////////////////////////////////////////////////
typedef sprite::sprite_ref sprite_ref;
