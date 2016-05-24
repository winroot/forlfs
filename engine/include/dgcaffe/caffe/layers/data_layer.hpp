#ifndef CAFFE_DATA_LAYER_HPP_
#define CAFFE_DATA_LAYER_HPP_

#include <vector>

#include "../blob.hpp"
#include "../data_reader.hpp"
#include "../data_transformer.hpp"
#include "../internal_thread.hpp"
#include "../layer.hpp"
#include "base_data_layer.hpp"
#include "../proto/caffe.pb.h"
#include "../util/db.hpp"

namespace caffe {

template <typename Dtype>
class DataLayer : public BasePrefetchingDataLayer<Dtype> {
 public:
  explicit DataLayer(const LayerParameter& param);
  virtual ~DataLayer();
  virtual void DataLayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  // DataLayer uses DataReader instead for sharing for parallelism
  virtual inline bool ShareInParallel() const { return false; }
  virtual inline const char* type() const { return "Data"; }
  virtual inline int ExactNumBottomBlobs() const { return 0; }
  virtual inline int MinTopBlobs() const { return 1; }
  virtual inline int MaxTopBlobs() const { return 2; }

 protected:
  virtual void load_batch(Batch<Dtype>* batch);

  DataReader<Datum> reader_;
};

}  // namespace caffe

#endif  // CAFFE_DATA_LAYER_HPP_
