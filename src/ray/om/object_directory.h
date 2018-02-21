#ifndef RAY_OBJECTDIRECTORY_H
#define RAY_OBJECTDIRECTORY_H

#include "memory"
#include "vector"

#include "ray/id.h"
#include "ray/status.h"

using namespace std;

namespace ray {

class ObjectDirectoryInterface {
 public:

  // Callback for GetLocations.
  using Callback = function<void(ray::Status, const vector<ray::DBClientID>&)>;

  ObjectDirectoryInterface() = default;

  // Asynchronously obtain the locations of an object by ObjectID.
  // Returns UniqueID, which uniquely identifies an invocation of
  // this method. Status passed to the callback indicates the outcome
  // of invoking this method.
  virtual UniqueID GetLocations(const ObjectID &object,
                                const Callback &callback) = 0;

  // Cancels the invocation of the callback associated with callback_id.
  virtual Status Cancel(const UniqueID &callback_id) = 0;
};

// Ray ObjectDirectory declaration.
class ObjectDirectory : public ObjectDirectoryInterface {

 public:
  ObjectDirectory();

  UniqueID GetLocations(const ObjectID &object,
                        const Callback &callback) override;

  Status Cancel(const UniqueID &callback_id) override;

};

} // namespace ray

#endif // RAY_OBJECTDIRECTORY_H