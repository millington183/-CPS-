package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Product;
import com.flushbonading.cps.entity.dto.AddProductDTO;
import com.flushbonading.cps.entity.dto.SearchProductDTO;
import com.flushbonading.cps.entity.vo.DefectiveDataVO;
import com.flushbonading.cps.entity.vo.ProductDataVO;
import com.flushbonading.cps.entity.vo.ProductVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Mapper
public interface ProductMapper extends BaseMapper<Product> {
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
    Integer totalCounts(@Param("search") SearchProductDTO search);

    /**
     * 根据id删除
     *
     * @param id
     * @return
     */
    Integer deleteProductById(String id);

    /**
     * 增加一条产品数据
     *
     * @param add
     * @return
     */
    Integer insertAProduct(@Param("add") AddProductDTO add);

    /**
     * 得到物料及其对应的总量
     *
     * @param date
     * @return
     */
    List<ProductDataVO> getProductMap(String date);

    /**
     * 成品数
     *
     * @param startTime
     * @param endTime
     * @return
     */
    Integer getYieldNumber(@Param("startTime") String startTime, @Param("endTime") String endTime);

    /**
     * 不良品情况
     *
     * @return
     */
    List<DefectiveDataVO> getDefectiveData();
}
