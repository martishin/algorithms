#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


struct Thread {
    int id;
    long long next_free_time;

    Thread(int id): id(id), next_free_time(0) {}

    bool operator< (const Thread &other) const {
        if (next_free_time == other.next_free_time)
            return id > other.id;
        else
            return next_free_time > other.next_free_time;
    }
};


class JobQueue {
private:
    int num_workers;
    vector<int> jobs;

    vector<int> assigned_workers;
    vector<long long> start_times;

    void WriteResponse() const {
        for (int i = 0; i < jobs.size(); ++i) {
            cout << assigned_workers[i] << " " << start_times[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers >> m;
        jobs.resize(m);

        for(int i = 0; i < m; ++i)
            cin >> jobs[i];
    }

    void AssignJobs() {
        // TODO: replace this code with a faster algorithm.
        assigned_workers.resize(jobs.size());
        start_times.resize(jobs.size());
        vector<long long> next_free_time(num_workers, 0);
        for (int i = 0; i < jobs.size(); ++i) {
            int duration = jobs[i];
            int next_worker = 0;
            for (int j = 0; j < num_workers; ++j) {
                if (next_free_time[j] < next_free_time[next_worker])
                    next_worker = j;
            }
            assigned_workers[i] = next_worker;
            start_times[i] = next_free_time[next_worker];
            next_free_time[next_worker] += duration;
        }
    }

    void AssignJobsFast() {
        assigned_workers.resize(jobs.size());
        start_times.resize(jobs.size());

        priority_queue<Thread> threads;

        for (size_t i = 0; i < num_workers; ++i)
            threads.push(Thread(i));

        for (size_t i = 0; i < jobs.size(); ++i) {
            Thread free_thread = threads.top();
            threads.pop();

            assigned_workers[i] = free_thread.id;
            start_times[i] = free_thread.next_free_time;
            free_thread.next_free_time += jobs[i];
            threads.push(free_thread);
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobsFast();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
