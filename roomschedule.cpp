#include <vector>
#include <map>
#include <tuple>
#include <mutex>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <set>

class IntervalMap
{
private:
    std::map<int, std::vector<std::pair<int, int>>> intervals;
    
public:
    bool InsertIfNoOverlap(int room, int start, int end)
    {
        auto &vec = intervals[room];
        if (std::any_of(vec.begin(), vec.end(), [start, end](const std::pair<int, int> &p) {
            return start < p.second && end > p.first;
            
        })) {
            return false;
        }
        vec.push_back({start, end});
        std::sort(vec.begin(), vec.end());
        return true;
    }
    
    std::map<int, std::vector<std::pair<int, int>>> GetAllReserations() const {
        return intervals;
    }
};

class RoomScheduler
{
private:
    std::set<int> room_ids;
    IntervalMap reservations;
    std::mutex lock;
    
public:
    RoomScheduler(const std::vector<int> &initial_rooms)
    {
        for (auto id:initial_rooms)
        {
            room_ids.insert(id);
        }
    }
    
    void UpdateRooms(const std::vector<int> &new_rooms)
    {
        std::lock_guard<std::mutex> guard(lock);
        for (auto id:new_rooms)
        {
            room_ids.insert(id);
        }
    }
    
    std::map<int, std::vector<std::pair<int, int>>> Schedule(const std::vector<std::tuple<int, int, int>> &inputs)
    {
        std::lock_guard<std::mutex> guard(lock);
        std::map<int, std::vector<std::pair<int, int>>> result;
        for (const auto &input : inputs)
        {
            int room_id = std::get<0>(input);
            int start_time = std::get<1>(input);
            int end_time = std::get<2>(input);
            
            if (end_time <= start_time)
            {
                throw std::runtime_error("End time must be greater than start time");
            }
            
            if (room_ids.find(room_id) == room_ids.end())
            {
                throw std::runtime_error("Attempted to schedule in a non-existent room");
            }
            
            if (!reservations.InsertIfNoOverlap(room_id, start_time, end_time))
            {
                throw std::runtime_error("Failed to insert reservation due to overlap");
            }
        }
        
        return reservations.GetAllReserations();
    }
};

#include <cassert>

int main()
{
    // TEST
    RoomScheduler scheduler({101, 102, 103});
    scheduler.UpdateRooms({104, 105, 106});
    
    auto results = scheduler.Schedule({{101, 9, 11}, {106, 12, 14}, {102, 10, 12}, {103, 16, 18}});
    assert(results[101].size() == 1);
    // TEST_END
    
    // TEST
    assert(results[106].size() == 1);
    // TEST_END
    
    // TEST
    assert(results[102].size() == 1);
    // TEST_END
    
    // TEST
    assert(results[103].size() == 1);
    // TEST_END

    // TEST
    assert(results.find(104) == results.end());
    // TEST_END
    
    // TEST
    try {
        scheduler.Schedule({{101, 11, 13}, {102, 9, 11}, {103, 17, 19}});
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
    // TEST_END
    
    // TEST
    try {
        scheduler.Schedule({{101, 14, 13}, {104, 15, 15}});
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
    // TEST_END
    
    // TEST
    try {
        scheduler.Schedule({{107, 11, 13}});
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
    // TEST_END
    
    //TEST
    auto back_to_back_booking = scheduler.Schedule({{105, 8, 10}, {105, 10, 12}});
    assert(back_to_back_booking[105].size() == 2);
    // TEST_END
    
    return 0;
}
