from collections import defaultdict


timestamp = [1, 2, 3]
serviceId = ["svc1", "svc2", "svc1"]
threshold = 1

result = {}
def detector(timestamp, serviceId, threshold):
    for num, label in zip(timestamp, serviceId):
        if label not in result:
            result[label] = []
        result[label].append(num)

    for key, val in result.items():
        diff = max(val) - min(val)
        if diff > threshold:
            print(key)



detector(timestamp, serviceId, threshold)