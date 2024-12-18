Drawable::Drawable(const std::string& sprite, Vector<float> size, float rotation) {
  this->size = size;
  this->sprite = sprite;
  this->rotation = rotation;
}

  const Vector<float>& get_size() const{
    return size;
  }

  
  const std::string& get_sprite() const{
    return sprite;
  }

  const float get_rotation() const{
    return rotation;
  }

  void set_rotation(float amount){
    rotation = amount; 
  }
