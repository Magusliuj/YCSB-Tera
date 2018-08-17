### Cloud Serving Database Benchmark for Baidu Tera

* This is a framework and common set of workloads for evaluating the performance of Baidu Tera “key-value” and “cloud” serving stores. 
* **The Client**: set up the database, choose the appropriate DB interface layer, runtime parameters and appropriate workload, load the data, execute the workload and then return the used time and throughout of the workload as an evaluating result.
* **An extensible workload generator**: generate the random loading data before executing.
* **The Core workloads**: a set of workload scenarios to be executed by the generator. The workload is designed to mimic the common scenarios when we use the “cloud” serving stores to support the real application. For example, Workload B: Read mostly workload which has a 95/5 read/write mix is used for photo tagging in real life: add a tag is an update, but most operations are to read tags.
* The benchmark tool is used to test Baidu Tera Distributed Database System to help find up some Optimizable points of "Tera".


