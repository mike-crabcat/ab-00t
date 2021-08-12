#pragma once

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <memory>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

/**
 * Triangulation file from Maptek Vulcan. Basically the file is a BTree of
 * compressed pagesof .
 * 
 * The logical address space is divided in pages whose size is determined by
 * `compression_block_size`. Each page has therefore a page index which is
 * simply offset / compression_block_size. Pages are then stored on disk
 * compressed.
 * 
 * A BTree is then used to map pages to disk. The internal nodes are 0x800
 * bytes in size and have 256 pointers, one for each of the four bytes of
 * making the page index. Pointers are 64 bit absolute offsets in the file.
 * 
 * The leafs of the BTree then store the compressed page, including
 * information like the size of the compressed page on disk and the size of
 * the compressed data. The compressed data can be smaller than the page
 * size and, if that case, it would be padded with zeroes.
 */

class vulcan_00t_t : public kaitai::kstruct {

public:
    class level1_pointer_t;
    class root_t;
    class page_t;
    class other_roots_t;
    class level0_pointer_t;
    class level2_pointer_t;
    class level3_pointer_t;

    enum compression_style_t {
        COMPRESSION_STYLE_LZF = 4
    };

    vulcan_00t_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

private:
    void _read();
    void _clean_up();

public:
    ~vulcan_00t_t();

    class level1_pointer_t : public kaitai::kstruct {

    public:

        level1_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::level0_pointer_t* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~level1_pointer_t();

    private:
        bool f_children;
        std::unique_ptr<std::vector<std::unique_ptr<level2_pointer_t>>> m_children;
        bool n_children;

    public:
        bool _is_null_children() { children(); return n_children; };

    private:

    public:
        std::vector<std::unique_ptr<level2_pointer_t>>* children();

    private:
        uint64_t m_disk_offset;
        uint64_t m_index;
        vulcan_00t_t* m__root;
        vulcan_00t_t::level0_pointer_t* m__parent;

    public:
        uint64_t disk_offset() const { return m_disk_offset; }
        uint64_t index() const { return m_index; }
        vulcan_00t_t* _root() const { return m__root; }
        vulcan_00t_t::level0_pointer_t* _parent() const { return m__parent; }
    };

    class root_t : public kaitai::kstruct {

    public:

        root_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~root_t();

    private:
        bool f_children;
        std::unique_ptr<std::vector<std::unique_ptr<level0_pointer_t>>> m_children;
        bool n_children;

    public:
        bool _is_null_children() { children(); return n_children; };

    private:

    public:
        std::vector<std::unique_ptr<level0_pointer_t>>* children();

    private:
        uint64_t m_disk_offset;
        uint64_t m_max_offset;
        vulcan_00t_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint64_t disk_offset() const { return m_disk_offset; }
        uint64_t max_offset() const { return m_max_offset; }
        vulcan_00t_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    /**
     * This represent a page of the logical address space, compressed according
     * to compression_style. The page includes logical addresses from page start
     * to page end (exclusive).
     */

    class page_t : public kaitai::kstruct {

    public:

        page_t(uint64_t p_page_index, kaitai::kstream* p__io, vulcan_00t_t::level3_pointer_t* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~page_t();

    private:
        bool f_page_start;
        int32_t m_page_start;

    public:
        int32_t page_start();

    private:
        bool f_page_end;
        int32_t m_page_end;

    public:
        int32_t page_end();

    private:
        uint32_t m_compressed_data_size;
        uint32_t m_disk_page_size;
        std::string m_compressed_data;
        uint64_t m_page_index;
        vulcan_00t_t* m__root;
        vulcan_00t_t::level3_pointer_t* m__parent;

    public:
        uint32_t compressed_data_size() const { return m_compressed_data_size; }
        uint32_t disk_page_size() const { return m_disk_page_size; }
        std::string compressed_data() const { return m_compressed_data; }
        uint64_t page_index() const { return m_page_index; }
        vulcan_00t_t* _root() const { return m__root; }
        vulcan_00t_t::level3_pointer_t* _parent() const { return m__parent; }
    };

    class other_roots_t : public kaitai::kstruct {

    public:

        other_roots_t(kaitai::kstream* p__io, vulcan_00t_t* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~other_roots_t();

    private:
        uint32_t m_num_roots;
        std::unique_ptr<std::vector<std::unique_ptr<root_t>>> m_other_roots;
        vulcan_00t_t* m__root;
        vulcan_00t_t* m__parent;

    public:
        uint32_t num_roots() const { return m_num_roots; }
        std::vector<std::unique_ptr<root_t>>* other_roots() const { return m_other_roots.get(); }
        vulcan_00t_t* _root() const { return m__root; }
        vulcan_00t_t* _parent() const { return m__parent; }
    };

    class level0_pointer_t : public kaitai::kstruct {

    public:

        level0_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::root_t* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~level0_pointer_t();

    private:
        bool f_children;
        std::unique_ptr<std::vector<std::unique_ptr<level1_pointer_t>>> m_children;
        bool n_children;

    public:
        bool _is_null_children() { children(); return n_children; };

    private:

    public:
        std::vector<std::unique_ptr<level1_pointer_t>>* children();

    private:
        uint64_t m_disk_offset;
        uint64_t m_index;
        vulcan_00t_t* m__root;
        vulcan_00t_t::root_t* m__parent;

    public:
        uint64_t disk_offset() const { return m_disk_offset; }
        uint64_t index() const { return m_index; }
        vulcan_00t_t* _root() const { return m__root; }
        vulcan_00t_t::root_t* _parent() const { return m__parent; }
    };

    class level2_pointer_t : public kaitai::kstruct {

    public:

        level2_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::level1_pointer_t* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~level2_pointer_t();

    private:
        bool f_children;
        std::unique_ptr<std::vector<std::unique_ptr<level3_pointer_t>>> m_children;
        bool n_children;

    public:
        bool _is_null_children() { children(); return n_children; };

    private:

    public:
        std::vector<std::unique_ptr<level3_pointer_t>>* children();

    private:
        uint64_t m_disk_offset;
        uint64_t m_index;
        vulcan_00t_t* m__root;
        vulcan_00t_t::level1_pointer_t* m__parent;

    public:
        uint64_t disk_offset() const { return m_disk_offset; }
        uint64_t index() const { return m_index; }
        vulcan_00t_t* _root() const { return m__root; }
        vulcan_00t_t::level1_pointer_t* _parent() const { return m__parent; }
    };

    class level3_pointer_t : public kaitai::kstruct {

    public:

        level3_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::level2_pointer_t* p__parent = nullptr, vulcan_00t_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~level3_pointer_t();

    private:
        bool f_page;
        std::unique_ptr<page_t> m_page;
        bool n_page;

    public:
        bool _is_null_page() { page(); return n_page; };

    private:

    public:
        page_t* page();

    private:
        uint64_t m_disk_offset;
        uint64_t m_index;
        vulcan_00t_t* m__root;
        vulcan_00t_t::level2_pointer_t* m__parent;

    public:
        uint64_t disk_offset() const { return m_disk_offset; }
        uint64_t index() const { return m_index; }
        vulcan_00t_t* _root() const { return m__root; }
        vulcan_00t_t::level2_pointer_t* _parent() const { return m__parent; }
    };

private:
    std::string m_signature;
    uint32_t m_format;
    compression_style_t m_compression_style;
    uint32_t m_compression_level;
    uint32_t m_compression_block_size;
    std::unique_ptr<root_t> m_root;
    std::unique_ptr<other_roots_t> m_other_roots;
    bool n_other_roots;

public:
    bool _is_null_other_roots() { other_roots(); return n_other_roots; };

private:
    vulcan_00t_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string signature() const { return m_signature; }
    uint32_t format() const { return m_format; }
    compression_style_t compression_style() const { return m_compression_style; }
    uint32_t compression_level() const { return m_compression_level; }
    uint32_t compression_block_size() const { return m_compression_block_size; }
    root_t* root() const { return m_root.get(); }
    other_roots_t* other_roots() const { return m_other_roots.get(); }
    vulcan_00t_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};
