#include "tool.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    Tool tool;
    tool.setup(argv[1]);
    tool.get_max_flow();

    std::cout << "#SubmissionId,ReviewerId,Match\n";
    for (output out : tool.submissions_output) {
        std::cout << out.id_orig << " " << out.id_dest << " " << out.match << std::endl;
    }
    std::cout << "#Total: " << tool.submissions_output.size() << std::endl;

    std::cout << "#ReviewerId,SubmissionId,Match\n";
    for (output out : tool.reviewers_output) {
        std::cout << out.id_orig << " " << out.id_dest << " " << out.match << std::endl;
    }
    std::cout << "#Total: " << tool.reviewers_output.size() << std::endl;
}
