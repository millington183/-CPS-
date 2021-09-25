package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Product;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddProductDTO;
import com.flushbonading.cps.entity.dto.SearchProductDTO;
import com.flushbonading.cps.entity.vo.DefectiveDataVO;
import com.flushbonading.cps.entity.vo.ProductVO;

import java.util.List;
import java.util.Map;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
public interface ProductService extends IService<Product> {
    /**
     * 查询每一总牌号对应的生产数量
     *
     * @return 返回List<Map < K, V>> K代表牌号，V代表数量
     */
    List<Map<String, Object>> getAllCountsByDifferentMaterial();

    /**
     * 分页查询所有产品信息
     *
     * @param search
     * @param page
     * @return
     */
    List<ProductVO> getAllProductMessage(SearchProductDTO search, Integer page);

    /**
     * 得到所有数量
     *
     * @param search
     * @return
     */
    Integer totalCounts(SearchProductDTO search);

    /**
     * 得到所有页面数
     *
     * @param search
     * @return
     */
    Integer totalPages(SearchProductDTO search);

    /**
     * 根据id删除
     *
     * @param id
     * @return
     */
    RespBean deleteProductById(String id);

    /**
     * 增加一条产品数据
     *
     * @param add
     * @return
     */
    RespBean insertAProduct(AddProductDTO add);

    /**
     * 获得牌号对应数据
     *
     * @return
     */
    List<String> getBrandData(List<String> brandName);

    /**
     * 得到成品率数据
     *
     * @return
     */
    List<String> getYieldData();

    /**
     * 不良品
     *
     * @return
     */
    List<DefectiveDataVO> getDefectiveData();
}
