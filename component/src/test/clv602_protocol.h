
#include <string>

namespace gomros {
namespace device {
class Clv602Protocol {
 public:
  typedef enum { ProcessFail, NoRead, ReadSuccess } RetType;

 public:
  Clv602Protocol(const std::string head = "#", const std::string rear = "%",
                 const std::string noread = "NoRead");

  RetType Process(const char* data, int size, std::string& result);

 private:
  std::string head, rear, noread;

  bool readhead = false;
  bool readrear = false;
  std::string buff;
};

}  // namespace device
}  // namespace gomros