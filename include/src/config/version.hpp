#ifndef REDWALK_VERSION_HPP
#define REDWALK_VERSION_HPP

#define REDWALK_VERSION "0.1.0"
#define REDWALK_MAJOR_VERSION 0
#define REDWALK_MINOR_VERSION 1
#define REDWALK_PATCH_VERSION 0

#define REDWALK_VERSION_AT_LEAST(x,y,z) ((REDWALK_MAJOR_VERSION>=x) && \
                                         (REDWALK_MINOR_VERSION>=y) && \
                                         (REDWALK_PATCH_VERSION>=z))

#define REDWALK_VERSION_AT_LEAST(x,y) ((REDWALK_MAJOR_VERSION>=x) && \
                                       (REDWALK_MINOR_VERSION>=y))

#endif //REDWALK_VERSION_HPP
